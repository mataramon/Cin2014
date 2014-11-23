package com.example.angel.luis;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContentValues;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.database.Cursor;

public class Init extends Activity {
    //

/// Variables and Handlers
    Logic business;
    Button showLocation;
    String url;
    private SQLiteDatabase database;
    private Db db;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_init);

        db = new Db(Init.this);

        showLocation = (Button) findViewById(R.id.showLocation);
        showLocation.setOnClickListener(new View.OnClickListener(){
                                            @Override
                                            public void onClick(View arg0){
                                                business = new Logic(Init.this);
                                                // Post location
                                                if(business.ableGetLocation()){
                                                    double latitude  = business.getLatitude();
                                                    double longitude = business.getLongitude();
                                                    Toast.makeText(getApplicationContext(), "Tus coordendas son\n Latitud " + latitude + "\n Longitud " + longitude, Toast.LENGTH_LONG).show();
                                                    SQLiteDatabase WriteDb = db.getWritableDatabase();

                                                    ContentValues values = new ContentValues();
                                                    //lat TEXT, longi
                                                    values.put("lat" , String.valueOf(latitude));
                                                    values.put("longi",String.valueOf(longitude));

                                                    long newRowId;
                                                    newRowId = WriteDb.insert(
                                                            "localizations",null, values);
                                                    WriteDb.close();

                                                    SQLiteDatabase ReadDb = db.getReadableDatabase();

                                                    String[] tables = {"lat", "longi"};

                                                    Cursor i = ReadDb.rawQuery("select * from localizations", null);
                                                    AlertDialog.Builder alertDialog = new AlertDialog.Builder(Init.this);
                                                    alertDialog.setTitle("-------- tarararan .... ");
                                                    alertDialog.setMessage(String.valueOf(i.getCount()));
                                                    alertDialog.show();

                                                    ReadDb.close();

                                                }else{
                                                    business.showSettingsAlert();

                                                }
                                            }
                                        }
        );


    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_init, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
