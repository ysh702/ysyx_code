#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512//姓名和邮箱的最大长度
#define MAX_ROWS 100//最大记录数
//地址结构体，表示一条记录(一个联系人）
struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};
//数据库结构体，包含所有联系人
struct Database {
    struct Address rows[MAX_ROWS];//100个联系人的数组
};
//连接数据库和文件，包含文件和数据库指针
struct Connection {
    FILE *file;//数据库文件指针
    struct Database *db;//数据库指针
};
//辅助函数：错误处理函数
void die(const char *message)
{//打印错误信息并退出程序
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}
//打印地址信息
void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}
//加载数据库
void Database_load(struct Connection *conn)
{//从文件读取整个数据库到内存
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to load database.");
}
//打开或创建数据库文件
struct Connection *Database_open(const char *filename, char mode)
{//分配连接结构体内存
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error");
//分配数据库内存
    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error");
//根据模式打开文件
    if(mode == 'c') {
        conn->file = fopen(filename, "w");//创建模式
    } else {
        conn->file = fopen(filename, "r+");//读写模式

        if(conn->file) {
            Database_load(conn);//加载已有数据库
        }
    }

    if(!conn->file) die("Failed to open the file");

    return conn;
}
//关闭数据库连接
void Database_close(struct Connection *conn)
{
    if(conn) {
        if(conn->file) fclose(conn->file);//关闭文件
        if(conn->db) free(conn->db);//释放数据库内存
        free(conn);//释放连接内存
    }
}
//写入数据库到文件
void Database_write(struct Connection *conn)
{
    rewind(conn->file);//回到文件开头
//写入整个数据库
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to write database.");

    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.");
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for(i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first");

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    if(!res) die("Email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if(argc > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("There's not that many records.");

    switch(action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get");

            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}
