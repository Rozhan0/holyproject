/*
    this library is a utility for permanent data storage using files.
    it provides functions to read and modify data in a file using structures.
*/
#include "database.h"
#define DEBUG 1

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

    FILE * file = fopen(path, "rb");
    if(file == 0 ) {
        DEBUG && puts("Database File Not Found!");
        exit(-1);
    }
    size_t size = size_of_file(file);
    database db = {path, 0, 0};
    db.length = size / sizeof(row);
    db.rows = calloc(db.length, sizeof(row));
    fread(db.rows, sizeof(row), db.length, file);
    fclose(file);
    return db;
}

void dump_database(database db) {
    /* this function writes an array of rows
    from database structure to database file */

    FILE * file = fopen(db.path, "wb");
    if(file == 0 ) {
        DEBUG && puts("Database File Not Found!");
        exit(-1);
    }
    fwrite(db.rows, sizeof(row), db.length, file);
    fclose(file);
}

void add_row(
        database * db,
        const char * id,
        const char * precedence,
        const char * date,
        const char * done,
        const char * description) {
    /* this function adds a row structure
    into array of rows in database structure */

    if(db == 0) {
        DEBUG && puts("in add_row function, database pointer is null!");
        exit(-1);
    }
    if(get_row(*db, id)) {
        DEBUG && puts("a row with same id already exists.");
        return;
    }
    db->length++;
    db->rows = realloc(db->rows, db->length * sizeof(row));
    strcpy(db->rows[db->length - 1].id, id);
    strcpy(db->rows[db->length - 1].precedence, precedence);
    strcpy(db->rows[db->length - 1].date, date);
    strcpy(db->rows[db->length - 1].done, done);
    strcpy(db->rows[db->length - 1].description, description);
}

row * get_row(database db, const char * id) {
    /* this function returns a row with given id
    from database.rows array */

    for (size_t i = 0; i < db.length; i++) {
        if(strncmp(db.rows[i].id, id, 3) == 0) {
            return db.rows + i;
        }
    }
    DEBUG && puts("row Not Found");
    return 0;
}

void copy_rows(row * dest_row, row * src_row, _Bool swap) {
    /* this function copies the source row to destination row
    or if swap is 1 it swaps the rows */

    if(swap) {
        row temp = *dest_row;
        memcpy(dest_row, src_row, sizeof(row));
        memcpy(src_row, &temp, sizeof(row));
    } else {
        memcpy(dest_row, src_row, sizeof(row));
    }
}

void del_row(database * db, const char * id) {
    for (size_t i = 0; i < db->length; i++) {
        if(strncmp(db->rows[i].id, id, 3) == 0) {
            if(i < db->length - 1) { /* if deleted row is not the last row */
                copy_rows(db->rows + i, db->rows + db->length - 1, 0);
            }
            db->length--;
            db->rows = realloc(db->rows, db->length * sizeof(row));
            return;
        }
    }
    DEBUG && puts("row Not Found");

}

void print_row(row * r) {
    (r != 0) && printf("%s %s %s %s %s\n",
                        r->id,
                        r->precedence,
                        r->date,
                        r->done,
                        r->description);
}
