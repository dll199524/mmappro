package com.example.mmappro

import android.app.Presentation
import android.content.Context
import android.os.Bundle
import android.view.Display

class DifferentDisplay(context : Context, display: Display)
    :Presentation(context, display) {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout)
    }

    }
