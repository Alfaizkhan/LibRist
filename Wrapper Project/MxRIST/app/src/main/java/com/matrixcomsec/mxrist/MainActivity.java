package com.matrixcomsec.mxrist;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.matrixcomsec.mxrist.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'mxrist' library on application startup.
    static {
        try{
            System.loadLibrary("rist");
            System.loadLibrary("MxRIST");
        }
        catch(UnsatisfiedLinkError ex)
        {
            Log.e("RIST", ex.toString());
        }
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText("Test");
    }
}