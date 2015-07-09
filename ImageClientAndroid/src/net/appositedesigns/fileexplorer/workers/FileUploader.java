package net.appositedesigns.fileexplorer.workers;

import android.app.ProgressDialog;
import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;
import net.appositedesigns.fileexplorer.activity.FileListActivity;
import net.appositedesigns.fileexplorer.model.FileListEntry;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;
import java.sql.Connection;

public class FileUploader extends AsyncTask<FileListEntry,String,String>
{

    private static final String TAG = FileUploader.class.getName();

    private FileListActivity caller;
    private ProgressDialog waitDialog;
    private Context context;
    private boolean success = false;
    private File currentDir;

    public FileUploader(FileListActivity caller) {
        this.caller = caller;
    }

    @Override
    protected void onPostExecute(String result) {

        Log.v(TAG, "Download completed");

        if(waitDialog!=null && waitDialog.isShowing())
        {
            waitDialog.dismiss();
        }
    }

    @Override
    // protected String doInBackground(String... sUrl) {
    protected String doInBackground(FileListEntry... sUrl) {

        Thread waitForASec = new Thread() {

            @Override
            public void run() {

                waitDialog = new ProgressDialog(caller);
                waitDialog.setTitle("");
                waitDialog.setMessage("Uploading online .....");
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

                                Toast toast = Toast.makeText(context, "Unable to go online....", Toast.LENGTH_LONG);
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


        caller.runOnUiThread(waitForASec);

        String upLoadServerUri = caller.getBackupUrl();
        HttpURLConnection conn = null;
        DataOutputStream dos = null;
        String lineEnd = "";

        int bytesRead, bytesAvailable, bufferSize;
        byte[] buffer;
        int maxBufferSize = 1 * 1024 * 1024;

        File sourceFile = new File(sUrl[0].getPath().getPath());
        try {

            // open a URL connection to the Servlet
            FileInputStream fileInputStream = new FileInputStream(sourceFile);
            URL url = new URL(upLoadServerUri);

            // Open a HTTP  connection to  the URL
            conn = (HttpURLConnection) url.openConnection();
            conn.setChunkedStreamingMode(1024);
            conn.setDoInput(true); // Allow Inputs
            conn.setDoOutput(true); // Allow Outputs
            conn.setUseCaches(false); // Don't use a Cached Copy
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Connection", "Keep-Alive");
            conn.setRequestProperty("Content-Type", "multipart/form-data;boundary=");
            conn.setRequestProperty("FileName",sourceFile.getName());

            conn.setRequestProperty("FileSize", String.valueOf(sUrl[0].getSize()));


            dos = new DataOutputStream(conn.getOutputStream());

            dos.writeBytes(lineEnd);

            // create a buffer of  maximum size
            bytesAvailable = fileInputStream.available();

            bufferSize = Math.min(bytesAvailable, maxBufferSize);
            buffer = new byte[bufferSize];

            // read file and write it into form...
            bytesRead = fileInputStream.read(buffer, 0, bufferSize);

            while (bytesRead > 0) {
                dos.write(buffer, 0, bufferSize);
                bytesAvailable = fileInputStream.available();
                bufferSize = Math.min(bytesAvailable, maxBufferSize);
                bytesRead = fileInputStream.read(buffer, 0, bufferSize);
            }

            // send multipart form data necesssary after file data...
            dos.writeBytes(lineEnd);

            int serverResponseCode = conn.getResponseCode();
            String serverResponseMessage = conn.getResponseMessage();

            Log.i("uploadFile", "HTTP Response is : "
                    + serverResponseMessage + ": " + serverResponseCode);

            if(serverResponseCode == 200){
                success = true;
            }

            //close the streams //
            fileInputStream.close();
            dos.flush();
            dos.close();
        }

        catch (FileNotFoundException e) {
            caller.runOnUiThread(waitForASec_toast);
        }
        catch (MalformedURLException e) {
            caller.runOnUiThread(waitForASec_toast);
        }
        catch (ProtocolException e) {
            caller.runOnUiThread(waitForASec_toast);
        }
        catch (IOException e) {
            //connection failed.
            caller.runOnUiThread(waitForASec_toast);
        }

        catch(Exception e) {
            caller.runOnUiThread(waitForASec_toast);
        }
        //stop the waiting dialog

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

        return null;
    }

}