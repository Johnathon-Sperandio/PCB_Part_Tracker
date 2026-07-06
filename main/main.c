
// this is the example given for C/C++ interface with sqlite3 in "https://sqlite.org/quickstart.html"
// acting as a init starting point.

#include <stdio.h>
#include <sqlite3.h>
#include <string.h>


static int callback(void *data, int argc, char **argv, char **azColName){
int i;
    int *col_name_flag = (int*)data;
    if(*col_name_flag){
        printf("|");
        for(i=0; i<argc; i++){
            printf(" %-10.10s |", azColName[i]);
        }
        printf("\n");
        *col_name_flag = 0;
    }
    printf("\n|");
    for(i=0; i<argc-1; i++){
        printf(" %-10.10s |", argv[i] ? argv[i] : "NULL");
    }
    printf(" %-30.30s |", argv[argc-1] ? argv[argc-1] : "NULL");

    return 0;
}

int main(int argc, char **argv){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    if( argc!=3 ){
        fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
        return(1);
    }
    rc = sqlite3_open(argv[1], &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(1);
    }
    int first_row = 1;
    rc = sqlite3_exec(db, "SELECT * FROM components;", callback, &first_row, &zErrMsg);
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    printf("\n");
    sqlite3_close(db);
    return 0;
}
