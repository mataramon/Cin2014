package com.example.angel.luis;


import android.app.AlertDialog;
import android.content.DialogInterface;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.content.Context;
import android.os.Bundle;
import android.os.IBinder;
import android.provider.Settings;
import android.util.Log;
import android.content.Intent;
import android.app.Service;

/**
 * Created by leofigy on 11/12/2014.
 */
public class Logic extends Service implements LocationListener {

    /**************************
     * Data structures
     *************************/
    // Regular locations
    private final Context mContext;
    boolean isGPSEnable = false;
    boolean isNetEnable = false;
    boolean ableGetLocation = false;
    protected LocationManager locationManager;

    // Items to store the location
    Location location;
    double latitude;
    double longitude;

    // Modifications
    private static final long MIN_DISTANCE_UPDATES = 20; //Meters
    private static final long MIN_TIME_UPDATES = 1000 * 60 * 1; // Minute

    // Constructor
    public Logic(Context context){
        this.mContext = context;
        getLocation();
    }

    public Location getLocation(){
        try{
            locationManager = (LocationManager) mContext.getSystemService(Context.LOCATION_SERVICE);
            isGPSEnable = locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
            isNetEnable = locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER);

            if(isGPSEnable || isNetEnable){
                this.ableGetLocation = true;

            }

            if (isNetEnable){
                locationManager.requestLocationUpdates(
                        LocationManager.NETWORK_PROVIDER,
                        MIN_TIME_UPDATES,
                        MIN_DISTANCE_UPDATES,
                        this);

                Log.d("Network", "Network");
                if(locationManager != null){
                    location = locationManager.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);
                    if(location != null){
                        latitude  = location.getLatitude();
                        longitude = location.getLongitude();
                    }
                }
            }

            if (isGPSEnable){
                if (location == null){
                    locationManager.requestLocationUpdates(
                            LocationManager.GPS_PROVIDER,
                            MIN_TIME_UPDATES,
                            MIN_DISTANCE_UPDATES,
                            this);
                    Log.d("GPS Enabled", "GPS Enabled");
                    if (locationManager != null){
                        location = locationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);

                        if (location != null) {
                            latitude = location.getLatitude();
                            longitude = location.getLongitude();
                        }

                    }

                }

            }

        }catch (Exception e){
            e.printStackTrace();


        }

        return location;
    }

    // Overriding methods
    @Override
    public  void onLocationChanged(Location location){}
    @Override
    public  void onProviderDisabled(String provider){}
    @Override
    public void onProviderEnabled(String provider){}
    @Override
    public void onStatusChanged(String provider, int status, Bundle extras){}
    @Override
    public  IBinder onBind(Intent arg0){
        return null;
    }

    public double getLatitude(){
        if(location != null){
            latitude = location.getLatitude();
        }
        return latitude;
    }

    public double getLongitude(){
        if(location != null){
            longitude = location.getLongitude();
        }
        return longitude;
    }

    public boolean ableGetLocation(){
        return this.ableGetLocation;
    }

    // Alerts for the user
    public void showSettingsAlert(){
        AlertDialog.Builder alertDialog = new AlertDialog.Builder(mContext);
        alertDialog.setTitle("Configuracion GPS");
        alertDialog.setMessage("El GPS :(");
        alertDialog.setPositiveButton("Settings", new DialogInterface.OnClickListener(){
            public void onClick(DialogInterface dialog, int which){
                Intent intent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
                mContext.startActivity(intent);
            }
        });

        alertDialog.show();

    }

    public void stopUsingGPS(){
        if(locationManager != null){
            locationManager.removeUpdates(Logic.this);
        }
    }


}

