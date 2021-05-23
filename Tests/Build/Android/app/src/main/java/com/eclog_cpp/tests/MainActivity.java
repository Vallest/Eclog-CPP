package com.eclog_cpp.tests;

import androidx.appcompat.app.AppCompatActivity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity
{
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        tv_ = new TextView(this);

        setContentView(tv_);

        setAssetManager(getAssets());

        (new Thread() {
            @Override
            public void run() {
                runTestCases();
            }
        }).start();
    }

    public void message(String s)
    {
        Message msg = new Message();

        msg.what = 0;
        msg.obj = s;

        handler_.sendMessage(msg);
    }

    public native void setAssetManager(AssetManager assetManager);

    public native void runTestCases();

    private Handler handler_ = new Handler() {
        @Override
        public void handleMessage(Message msg)
        {
            super.handleMessage(msg);
            switch (msg.what)
            {
                case 0:
                    tv_.append((String)msg.obj);
                    break;
            }
        }
    };

    private TextView tv_;
}

