package com.example.mmappro;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Environment;
import android.widget.TextView;

import com.example.mmappro.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'mmappro' library on application startup.
    static {
        System.loadLibrary("mmappro");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
        FileLogger logger = new FileLogger(Environment.getExternalStorageDirectory(), 4 * 1024 * 1024);
        logger.write("1234567");
    }

    /**
     * A native method that is implemented by the 'mmappro' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}