package net.appositedesigns.fileexplorer.workers;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URI;
import java.net.URL;
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
import android.content.Context;
import android.os.AsyncTask;
import android.util.Base64;
import android.util.Log;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONObject;

public class FileDownloader extends AsyncTask<String,String,String>
{

    private static final String TAG = Finder.class.getName();

    private FileListActivity caller;
    private ProgressDialog waitDialog;
    private Context context;

    private File currentDir;

    public FileDownloader(FileListActivity caller) {
        this.caller = caller;
    }

    @Override
    protected void onPostExecute(String result) {

        Log.v(TAG, "Download completed");

        if(waitDialog!=null && waitDialog.isShowing())
        {
            waitDialog.dismiss();
        }
       //caller.setCurrentDirAndChilren(currentDir,childFilesList);
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
    protected String doInBackground(String... sUrl) {

        Thread waitForASec = new Thread() {

            @Override
            public void run() {

                waitDialog = new ProgressDialog(caller);
                waitDialog.setTitle("");
                waitDialog.setMessage("Downloading online file.....");
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


        InputStream input = null;
        OutputStream output = null;
        HttpURLConnection connection = null;
        String filaName = sUrl[1];
        String url_download = sUrl[0];
        byte[] data_64 = null;
        try {
            data_64 = filaName.getBytes("UTF-8");
        } catch (UnsupportedEncodingException e1) {
            e1.printStackTrace();
        }
        String base64_file_name = Base64.encodeToString(data_64, Base64.DEFAULT);
        url_download += "?fileName="+ base64_file_name;

        try {
            URL url = new URL(url_download);
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            //connection.setDoOutput(false);
            connection.setChunkedStreamingMode(1024);
            connection.connect();

            // expect HTTP 200 OK, so we don't mistakenly save error report
            // instead of the file
            if (connection.getResponseCode() != HttpURLConnection.HTTP_OK) {

                switch(connection.getResponseCode()) {

                    case HttpURLConnection.HTTP_NOT_FOUND:
                        return "Server returned HTTP " + connection.getResponseCode()
                                + " " + connection.getResponseMessage();

                    default:
                        return "Server returned HTTP " + connection.getResponseCode()
                            + " " + connection.getResponseMessage();
                }

            }

            // this will be useful to display download percentage
            // might be -1: server did not report the length
            int fileLength = connection.getContentLength();

            // download the file

            input = connection.getInputStream();
            output = new FileOutputStream(caller.getBackupDir() + filaName);

            byte data[] = new byte[4096];
            long total = 0;
            int count;
            while ((count = input.read(data)) != -1) {
                // allow canceling with back button
                if (isCancelled()) {
                    input.close();
                    return null;
                }
                total += count;
                // publishing the progress....
                //if (fileLength > 0) // only if total length is known
                    //publishProgress((int) (total * 100 / fileLength));
                output.write(data, 0, count);
            }
        } catch (Exception e) {
            return e.toString();
        } finally {
            try {
                if (output != null)
                    output.close();
                if (input != null)
                    input.close();
            } catch (IOException ignored) {
            }

            if (connection != null)
                connection.disconnect();

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
        }

        return null;
    }

}