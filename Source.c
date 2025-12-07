#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int writefile(char* fname, struct Blog* blogs, int size);
void inputDate(struct Date* date);

enum Category {
    TECHNOLOGY,
    SCIENCE,
    ART,
    EDUCATION,
    OTHER
};

enum ModerStatus {
    PENDING,
    APPROVED,
    REJECTED
};

struct Date {
    int day;
    int month;
    int year;
};

struct Blog {
    char title[100];
    char author[50];
    enum Category category;
    struct Date date;
    int comments;
    double rating;
    enum ModerStatus status;
};


int main() {
    setlocale(LC_CTYPE, "RUS");
    int n;
    printf("Введите кол-во записей: ");
    scanf("%d", &n);
    getchar(); 

    struct Blog* blogs = (struct Blog*)malloc(n * sizeof(struct Blog));
    if (blogs == NULL) {
        printf("Ошибка\n");
        return 1;
    }

    printf("\nВвод данных о блогах\n");
    for (int i = 0; i < n; i++) {
        printf("\n--- Запись #%d ---\n", i + 1);

        printf("Введите заголовок (без пробелов, используйте '_'): ");
        fgets(blogs[i].title, 100, stdin);
        blogs[i].title[strcspn(blogs[i].title, "\n")] = '\0';

        printf("Введите автора (без пробелов, используйте '_'): ");
        fgets(blogs[i].author, 50, stdin);
        blogs[i].author[strcspn(blogs[i].author, "\n")] = '\0';

        int categoryChoice;
        printf("Выберите категорию:\n");
        printf("0 - TECHNOLOGY\n");
        printf("1 - SCIENCE\n");
        printf("2 - ART\n");
        printf("3 - EDUCATION\n");
        printf("4 - OTHER\n");
        printf("Ваш выбор: ");
        scanf("%d", &categoryChoice);

        if (categoryChoice >= 0 && categoryChoice <= 4) {
            blogs[i].category = (enum Category)categoryChoice;
        }
        else {
            printf("Некорректный выбор\n");
        }
        void inputDate(struct Date* date);
        printf("\nВведите дату публикации:\n");
        inputDate(&blogs[i].date);

        printf("Количество комментариев: ");
        scanf("%d", &blogs[i].comments);

        printf("Рейтинг (например, 4.5): ");
        scanf("%lf", &blogs[i].rating);

        int statusChoice;
        printf("Выберите статус модерации:\n");
        printf("0 - PENDING\n");
        printf("1 - APPROVED\n");
        printf("2 - REJECTED\n");
        printf("Ваш выбор: ");
        scanf("%d", &statusChoice);
        getchar(); 

        if (statusChoice >= 0 && statusChoice <= 2) {
            blogs[i].status = (enum ModerStatus)statusChoice;
        }
        else {
            printf("Некорректный выбор\n");
        }
    }

    char filename[100];
    printf("\nВведите имя файла (например, blogs.txt): ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    int writefile(char* filename, struct Blog* blogs, int n);

    if (writefile(filename, blogs, n)) {
        printf("\nДанные записаны в файл '%s'\n", filename);
    }
    free(blogs);

    return 0;
}

int writefile(char* fname, struct Blog* blogs, int size) {
    FILE* out;
    if ((out = fopen(fname, "wt")) == NULL) {
        printf("Ошибка открытия файла для записи\n");
        return 0;
    }

    for (int i = 0; i < size; i++) {
        char categoryStr[20];
        switch (blogs[i].category) {
        case TECHNOLOGY: strcpy(categoryStr, "TECHNOLOGY"); break;
        case SCIENCE: strcpy(categoryStr, "SCIENCE"); break;
        case ART: strcpy(categoryStr, "ART"); break;
        case EDUCATION: strcpy(categoryStr, "EDUCATION"); break;
        default: strcpy(categoryStr, "OTHER");
        }

        char statusStr[20];
        switch (blogs[i].status) {
        case PENDING: strcpy(statusStr, "PENDING"); break;
        case APPROVED: strcpy(statusStr, "APPROVED"); break;
        case REJECTED: strcpy(statusStr, "REJECTED"); break;
        }

        fprintf(out, "Заголовок:%s Автор:%s Категория:%s Дата:%02d.%02d.%04d Комментарии:%d Рейтинг:%.2f Статус:%s\n",
            blogs[i].title, blogs[i].author, categoryStr, blogs[i].date.day, blogs[i].date.month,
            blogs[i].date.year, blogs[i].comments, blogs[i].rating, statusStr);
    }

    fclose(out);
    return 1;
}
void inputDate(struct Date* date) {
    printf("День: ");
    scanf("%d", &date->day);
    printf("Месяц: ");
    scanf("%d", &date->month);
    printf("Год: ");
    scanf("%d", &date->year);
    getchar();
}