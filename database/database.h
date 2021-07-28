#ifndef DATABASE_H
#define DATABASE_H

struct row {
    char id[4];
    char precedence[2];
    char date[9];
    char done[2];
    char description[101];
} typedef row;

struct database {
    const char * path;
    row *rows;
    size_t length;
} typedef database;

size_t size_of_file(FILE * file);
database load_database(const char * path);
void dump_database(database db);
void add_row(database * db, row r);

#endif
