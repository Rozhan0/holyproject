#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct row {
    char id[4];
    char precedence[2];
    char date[9];
    char done[2];
    char description[101];
} typedef row;

struct database {
    const char * path;
    row * rows;
    size_t length;
} typedef database;

size_t size_of_file(FILE * file);
database load_database(const char * path);
void dump_database(database db);
void add_row(
    database * db,
    const char * id,
    const char * precedence,
    const char * date,
    const char * done,
    const char * description);
row * get_row(database db, const char * id);
void copy_rows(row * dest_row, row * src_row, _Bool swap);
void del_row(database * db, const char * id);
void print_row(row * r);

#endif
