/*
    this library is a utility for permanent data storage using files.
    it provides functions to read and modify data in a file using structures.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"


size_t size_of_file(FILE *file) {
    /* this function returns size of a file
    by seeking into end of file and using ftell
    to get byte count and then seek back to
    file's beginning */

    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return size;
}

database load_database(const char * path) {
    /* this function reads database file into
    an array of rows in database structure */

    FILE * file = fopen(path, "r");
    if(file == 0 ) {
        puts("Database File Not Found!");
        exit(-1);
    }
    size_t size = size_of_file(file);
    database db = {path, 0, 0};
    db.length = size / sizeof(db.rows[0]);
    db.rows = calloc(sizeof(row), db.length);
    fread(db.rows, sizeof(db.rows[0]), db.length, file);
    fclose(file);
    return db;
}

void dump_database(database db) {
    /* this function writes an array of rows
    from database structure to database file */

    FILE * file = fopen(db.path, "w");
    printf("%ld %ld\n", sizeof(db.rows[0]), db.length);
    fwrite(db.rows, sizeof(db.rows[0]), db.length, file);
    puts("fucked up");
    fclose(file);
}

void add_row(database * db, row r) {
    /* this function adds a row structure
    into array of rows in database structure */

    if(db == 0) {
        puts("in add_row function, database pointer is null!");
        exit(-1);
    }
    db->length++;
    db->rows = realloc(db->rows, db->length * sizeof(db->rows[0]));
    db->rows[db->length - 1] = r;
}
