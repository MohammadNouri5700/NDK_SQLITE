#include <jni.h>
#include <string>
#include "sqlite3.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <android/log.h>

#define APPNAME "DB_API"


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_sqlitetestr_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string msg = "Hello from C++";

    std::clock_t start;
    double duration;
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("/data/data/com.example.sqlitetestr/databases/FeedReader.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        msg = "Cannot open database:";
        return env->NewStringUTF(msg.c_str());
    }


    int mission  = 20;
    int counter = 500;
    int step = 100;
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "The insert to database begin");
    for (int j = 0;j < mission; ++j) {
        for (int i = 0; i < counter; ++i) {
            std::string sql = "INSERT INTO entry ('name','size','type','value') VALUES ('Jeff','12','integer','78141235');";
            rc = sqlite3_exec(db, sql.c_str(), NULL, NULL,NULL);
        }
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "%i successfully added", counter);
        counter+=step;
    }

    duration = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "The total time is %f", duration);

    sqlite3_close(db);


    return env->NewStringUTF(std::to_string(duration).c_str());
}