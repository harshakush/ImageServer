package net.appositedesigns.fileexplorer.workers;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URI;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.List;
import java.util.Map;

import net.appositedesigns.fileexplorer.R;
import net.appositedesigns.fileexplorer.activity.FileListActivity;
import net.appositedesigns.fileexplorer.model.FileListEntry;
import net.appositedesigns.fileexplorer.model.FileListing;
import net.appositedesigns.fileexplorer.util.FileListSorter;
import net.appositedesigns.fileexplorer.util.Util;
import android.app.ProgressDialog;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.ProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONObject;

public class Finder extends AsyncTask<File, Integer, FileListing>
{
	
	private static final String TAG = Finder.class.getName();
	
	private FileListActivity caller;
	private ProgressDialog waitDialog;
	
	private File currentDir;
	
	public Finder(FileListActivity caller) {
		this.caller = caller;
	}

	@Override
	protected void onPostExecute(FileListing result) {

		FileListing childFilesList = result;
		Log.v(TAG, "Children for "+currentDir.getAbsolutePath()+ " received");
		
		if(waitDialog!=null && waitDialog.isShowing())
		{
			waitDialog.dismiss();
		}
		Log.v(TAG, "Children for "+currentDir.getAbsolutePath()+" passed to caller");
		caller.setCurrentDirAndChilren(currentDir,childFilesList);
	
	}

    public void download_file(final String fileName) {

    }

    private String[] getOnlineList() {
        String[] list_return = null;
        HttpClient httpclient = new DefaultHttpClient();

        // Prepare a request object
        String url_str = caller.getBackupUrl();
        HttpGet httpget = new HttpGet(url_str);

        Thread waitForASec_toast = new Thread() {

            @Override
            public void run() {

                try {
                    Thread.sleep(100);
                    if(this.isInterrupted())
                    {
                        return;
                    }
                    else
                    {
                        caller.runOnUiThread(new Runnable() {

                            @Override
                            public void run() {

                                Toast toast = Toast.makeText(caller, "Unable to go online....", Toast.LENGTH_LONG);
                                toast.show();
                            }
                        });

                    }
                } catch (InterruptedException e) {
                    Log.e(TAG, "Toast thread encountered exception ",e);
                    e.printStackTrace();
                }
            }
        };

        // Execute the request
        HttpResponse response;
        try {
            response = httpclient.execute(httpget);
            // Examine the response status
            Log.i("Praeda",response.getStatusLine().toString());

            // Get hold of the response entity
            HttpEntity entity = response.getEntity();
            // If the response does not enclose an entity, there is no need
            // to worry about connection release

            if (entity != null) {

                // A Simple JSON Response Read
                InputStream instream = entity.getContent();
                String result= convertStreamToString(instream);
                // now you have the string representation of the HTML request
                instream.close();

                //
                JSONObject obj = new JSONObject((result));
                JSONArray array_obj = obj.getJSONArray("fileList");
                list_return = new String[array_obj.length()];

                for(int i=0;i<array_obj.length();i++) {
                    JSONObject temp_obj = array_obj.getJSONObject(i);
                    list_return[i] = temp_obj.getString("name");
                }
            }
        }

        catch (FileNotFoundException e) {
            caller.runOnUiThread(waitForASec_toast);
        }
        catch (MalformedURLException e) {
            caller.runOnUiThread(waitForASec_toast);
        } catch (IOException e) {
            //connection failed.
            caller.runOnUiThread(waitForASec_toast);
        }
        catch (Exception e) {
            //Catching all exceptions
            caller.runOnUiThread(waitForASec_toast);
        }



        return list_return;
    }

    private static String convertStreamToString(InputStream is) {
    /*
     * To convert the InputStream to String we use the BufferedReader.readLine()
     * method. We iterate until the BufferedReader return null which means
     * there's no more data to read. Each line will appended to a StringBuilder
     * and returned as String.
     */
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        StringBuilder sb = new StringBuilder();

        String line = null;
        try {
            while ((line = reader.readLine()) != null) {
                sb.append(line + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                is.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return sb.toString();
    }

	@Override
	protected FileListing doInBackground(File... params) {
		
		Thread waitForASec = new Thread() {
			
			@Override
			public void run() {
				
				waitDialog = new ProgressDialog(caller);
				waitDialog.setTitle("");
				waitDialog.setMessage(caller.getString(R.string.querying_filesys));
				waitDialog.setIndeterminate(true);
				
				try {
					Thread.sleep(100);
					if(this.isInterrupted())
					{
						return;
					}
					else
					{
						caller.runOnUiThread(new Runnable() {
							
							@Override
							public void run() {

								if(waitDialog!=null)
									waitDialog.show();
							}
						});

					}
				} catch (InterruptedException e) {
					
					Log.e(TAG, "Progressbar waiting thread encountered exception ",e);
					e.printStackTrace();
				}

				
			}
		};
		caller.runOnUiThread(waitForASec);
		
		currentDir = params[0];
		Log.v(TAG, "Received directory to list paths - "+ currentDir.getAbsolutePath());
        boolean online = false;
        String[] children = null;

        if(currentDir.getName().contains("Go_Online")) {
            online = true;
            children = getOnlineList();
        } else {
            children = currentDir.list();
        }

		FileListing listing = new FileListing(new ArrayList<FileListEntry>());
		List<FileListEntry> childFiles = listing.getChildren();

		boolean showHidden = caller.getPreferenceHelper().isShowHidden();
		boolean showSystem = caller.getPreferenceHelper().isShowSystemFiles();
		Map<String, Long> dirSizes = Util.getDirSizes(currentDir);

        if(!online) {
            for (String fileName : children) {
                if (".nomedia".equals(fileName)) {
                    listing.setExcludeFromMedia(true);
                }
                File f = new File(currentDir.getAbsolutePath() + File.separator + fileName);

                if (!f.exists()) {
                    continue;
                }
                if (Util.isProtected(f) && !showSystem) {
                    continue;
                }
                if (f.isHidden() && !showHidden) {
                    continue;
                }

                String fname = f.getName();

                FileListEntry child = new FileListEntry();
                child.setName(fname);
                child.setPath(f);
                if (f.isDirectory()) {
                    try {
                        Long dirSize = dirSizes.get(f.getCanonicalPath());
                        child.setSize(dirSize);
                    } catch (Exception e) {

                        Log.w(TAG, "Could not find size for " + child.getPath().getAbsolutePath());
                        child.setSize(0);
                    }
                } else {
                    child.setSize(f.length());
                }
                child.setLastModified(new Date(f.lastModified()));
                childFiles.add(child);
            }
        } else if(children != null) {

            for (String fileName : children) {
                FileListEntry child = new FileListEntry();
                child.setName(fileName);
                child.setPath(new File(fileName));
                child.setLastModified(new Date());
                child.setOnline();
                childFiles.add(child);
            }
        }
        else
        {
            return null;
        }

		FileListSorter sorter = new FileListSorter(caller);
		Collections.sort(childFiles, sorter);
		
		Log.v(TAG, "Will now interrupt thread waiting to show progress bar");
		if(waitForASec.isAlive())
		{
			try
			{
				waitForASec.interrupt();
			}
			catch (Exception e) {
				
				Log.e(TAG, "Error while interrupting thread",e);
			}
		}
		return listing;
	}
}
