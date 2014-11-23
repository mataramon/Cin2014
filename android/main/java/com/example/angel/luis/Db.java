package com.example.angel.luis;
import android.content.Context;
import android.database.sqlite.*;
import android.util.Log;


/**
 * Created by Angel on 23.11.2014.
 */

public class Db  extends SQLiteOpenHelper{

    private static final int DATABASE_VERSION = 1;
    private static final String DATABASE_NAME = "localizations.db";

    private static final String dataquery = "create table localizations (lat TEXT, longi TEXT);";

    public Db(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }



    @Override
    public void onCreate(SQLiteDatabase database) {
        database.execSQL(dataquery);
    }


    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        Log.w(Db.class.getName(),
                "Upgrading database from version " + oldVersion + " to "
                        + newVersion + ", which will destroy all old data");
        db.execSQL("DROP TABLE IF EXISTS " + "localizations");
        onCreate(db);
    }


}
