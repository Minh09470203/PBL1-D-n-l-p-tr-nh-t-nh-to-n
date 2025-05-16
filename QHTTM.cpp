#include <stdio.h>
#include <stdlib.h>

#define MAX 100
int M, N;
int basic[MAX]; // Lưu các biến cơ bản đang ở mỗi hàng

void printInfo() {
    printf("----------PROJECT----------\n");
    printf("PBL1: DU AN LAP TRINH TINH TOAN\n");
    printf("DE TAI: <BAI TOAN QUY HOACH TUYEN TINH> \n\n");
    printf("THANH VIEN:\n\n 1. LE QUANG DAT\n 2. NGUYEN DUC MINH\n 3. HUYNH NGUYEN ANH KIET\n\n");
    printf("MUC TIEU: THIET KE CHUONG TRINH GIAI BAI TOAN QUY HOACH TUYEN TINH:\n");
    printf("\nTOI DA HOA HAM MUC TIEU: Z = c1x1 + c2x2 + ... + cnxn\nVOI CAC RANG BUOC DANG:\n");
    printf("\n{a11x1 + a12x2 + ... + a1nxn <= b1\n{...\n{am1x1 + am2x2 + ... + amnxn <= bm\n xi>=0\n\n");
    printf("DU LIEU DAU VAO GOM:\n- SO RANG BUOC (M)\n- SO BIEN (N)\n- MA TRAN HE SO VA CAC GIA TRI GIOI HAN CUA TUNG RANG BUOC\n- HE SO CUA HAM MUC TIEU\n\n");
    printf("\nBAT DAU:\n\n");
}

void printTable(double t[MAX + 1][MAX + 1], FILE *fp, int choice) {
    if (choice == 2 && fp != NULL) {
        fprintf(fp, "\n=== BANG SIMPLEX ===\n");

        fprintf(fp, "+--------+");
        for (int j = 0; j < N; j++) {
            fprintf(fp, "---------+");
        }
        fprintf(fp, "---------+\n");

        fprintf(fp, "| Bien cb|");
        for (int j = 0; j < N; j++) {
            fprintf(fp, "   x%-3d |", j + 1);
        }
        fprintf(fp, "   RHS   |\n");

        fprintf(fp, "+--------+");
        for (int j = 0; j <= N; j++) {
            fprintf(fp, "---------+");
        }
        fprintf(fp, "\n");

        for (int i = 0; i <= M; i++) {
            if (i < M)
                fprintf(fp, "|   x%-3d |", basic[i] + 1);
            else
                fprintf(fp, "|   Z    |");

            for (int j = 0; j <= N; j++) {
                fprintf(fp, "%8.3lf|", t[i][j]);
            }
            fprintf(fp, "\n");

            fprintf(fp, "+--------+");
            for (int j = 0; j <= N; j++) {
                fprintf(fp, "---------+");
            }
            fprintf(fp, "\n");
        }
    } else {
        printf("\n=== BANG SIMPLEX ===\n");

        printf("+--------+");
        for (int j = 0; j < N; j++) {
            printf("---------+");
        }
        printf("---------+\n");

        printf("| Bien cb|");
        for (int j = 0; j < N; j++) {
            printf("   x%-3d |", j + 1);
        }
        printf("   RHS   |\n");

        printf("+--------+");
        for (int j = 0; j <= N; j++) {
            printf("---------+");
        }
        printf("\n");

        for (int i = 0; i <= M; i++) {
            if (i < M)
                printf("|   x%-3d |", basic[i] + 1);
            else
                printf("|   Z    |");

            for (int j = 0; j <= N; j++) {
                printf("%8.3lf|", t[i][j]);
            }
            printf("\n");

            printf("+--------+");
            for (int j = 0; j <= N; j++) {
                printf("---------+");
            }
            printf("\n");
        }
    }
}

int Col(double t[MAX + 1][MAX + 1]) {
    int c = -1;
    double maxValue = 0;
    for (int j = 0; j < N; j++) {
        if (t[M][j] > maxValue) {
            maxValue = t[M][j];
            c = j;
        }
    }
    return c;
}

int Row(double t[MAX + 1][MAX + 1], int c, FILE *fp, int choice) {
    int r = -1;
    double minRatio = 1e9;
    for (int i = 0; i < M; i++) {
        if (t[i][c] > 0) {
            double ratio = t[i][N] / t[i][c];
            if (choice == 2 && fp != NULL) {
                fprintf(fp, "Hang %d: RHS = %.3lf / pivot col = %.3lf --> ratio = %.3lf\n", i + 1, t[i][N], t[i][c], ratio);
            } else {
                printf("Hang %d: RHS = %.3lf / pivot col = %.3lf --> ratio = %.3lf\n", i + 1, t[i][N], t[i][c], ratio);
            }

            if (ratio < minRatio) {
                minRatio = ratio;
                r = i;
            }
        } else {
            if (choice == 2 && fp != NULL) {
                fprintf(fp, "Hang %d: bo qua vi he so pivot <= 0\n", i + 1);
            } else {
                printf("Hang %d: bo qua vi he so pivot <= 0\n", i + 1);
            }
        }
    }
    return r;
}

void Pivot(double t[MAX + 1][MAX + 1], int r, int c, FILE *fp, int choice) {
    double p = t[r][c];
    if (choice == 2 && fp != NULL) {
        fprintf(fp, "\nPivot tai o (%d, %d) = %.3lf\n", r + 1, c + 1, p);
        fprintf(fp, "Chia hang %d cho pivot:\n", r + 1);
    } else {
        printf("\nPivot tai o (%d, %d) = %.3lf\n", r + 1, c + 1, p);
        printf("Chia hang %d cho pivot:\n", r + 1);
    }

    for (int j = 0; j <= N; j++) t[r][j] /= p;

    if (choice == 2 && fp != NULL) {
        fprintf(fp, "Hang sau khi chia: ");
        for (int j = 0; j <= N; j++) {
            fprintf(fp, "%.3lf ", t[r][j]);
        }
        fprintf(fp, "\n");
    } else {
        printf("Hang sau khi chia: ");
        for (int j = 0; j <= N; j++) {
            printf("%.3lf ", t[r][j]);
        }
        printf("\n");
    }

    for (int i = 0; i <= M; i++) {
        if (i != r) {
            double f = t[i][c];
            if (choice == 2 && fp != NULL) {
                fprintf(fp, "Cap nhat hang %d\n", i + 1);
            } else {
                printf("Cap nhat hang %d\n", i + 1);
            }

            for (int j = 0; j <= N; j++) {
                t[i][j] -= f * t[r][j];
            }
        }
    }
    basic[r] = c; // cập nhật biến cơ bản
}

void SimplexMethod(double t[MAX + 1][MAX + 1], FILE *fp, int choice) {
    int step = 1;
    while (1) {
        int stop = 1;
        for (int j = 0; j < N; j++) {
            if (t[M][j] > 0) {
                stop = 0;
                break;
            }
        }
        if (stop) break;

        if (choice == 2 && fp != NULL) {
            fprintf(fp, "\n== LAN %d ==\n", step++);
        } else {
            printf("\n== LAN %d ==\n", step++);
        }

        int c = Col(t);

        if (choice == 2 && fp != NULL) {
            fprintf(fp, "Chon bien vao: x%d\n", c + 1);
        } else {
            printf("Chon bien vao: x%d\n", c + 1);
        }

        int r = Row(t, c, fp, choice);
        if (r == -1) {
            if (choice == 2 && fp != NULL) {
                fprintf(fp, "Bai toan khong gioi noi (khong co bien ra).\n");
            } else {
                printf("Bai toan khong gioi noi (khong co bien ra).\n");
            }
            return;
        }

        if (choice == 2 && fp != NULL) {
            fprintf(fp, "Chon bien ra: x%d\n", basic[r] + 1);
            Pivot(t, r, c, fp, choice);
            printTable(t, fp, choice);
        } else {
            printf("Chon bien ra: x%d\n", basic[r] + 1);
            Pivot(t, r, c, NULL, choice);
            printTable(t, NULL, choice);
        }
    }
}

void DocFile(FILE *fout) {
    char line[256];
    while (fgets(line, sizeof(line), fout)) {
        printf("%s", line);
    }
    fclose(fout);
}

int main() {
    double t[MAX + 1][MAX + 1];

    printInfo();

    int choice;

    do {
        printf("Chon cach nhap du lieu:\n1. Nhap tu ban phim\n2. Nhap va ghi vao file\nLua chon: ");
        scanf("%d", &choice);
        if (choice != 1 && choice != 2) {
            printf("\nLua chon khong hop le! vui long nhap lai.\n");
        }
    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        printf("Nhap so rang buoc M: ");
        scanf("%d", &M);
        printf("Nhap so bien N: ");
        scanf("%d", &N);

        printf("Nhap he so rang buoc va gioi han (dang <=):\n");
        for (int i = 0; i < M; i++) {
            for (int j = 0; j <= N; j++) {
                scanf("%lf", &t[i][j]);
            }
            basic[i] = N + i;
        }

        printf("Nhap he so ham muc tieu (dang MAX Z):\n");
        for (int j = 0; j < N; j++) {
            scanf("%lf", &t[M][j]);
        }
        t[M][N] = 0;
        printTable(t, NULL, choice);
        SimplexMethod(t, NULL, choice);

        printf("\n== KET QUA CUOI CUNG ==\n");

        printf("Gia tri toi uu Z = %lf\n", -t[M][N]);

        for (int j = 0; j < N; j++) {
            double value = 0;
            for (int i = 0; i < M; i++) {
                if (basic[i] == j) {
                    value = t[i][N];
                    break;
                }
            }
            printf("x%d = %lf\n", j + 1, value);
        }
    } else if (choice == 2) {
        char saveFile[100];
        FILE *saveFp = NULL;
        printf("Nhap ten file de ghi du lieu: ");
        scanf("%s", saveFile);
        
        saveFp = fopen(saveFile, "w");
        
        if (saveFp == NULL) {
            printf("Khong the tao file %s\n", saveFile);
            return 1;
        }

        printf("Nhap so rang buoc M: ");
        scanf("%d", &M);

        printf("Nhap so bien N: ");
        scanf("%d", &N);

        fprintf(saveFp, "%d %d\n", M, N);
        printf("Nhap he so rang buoc va gioi han (dang <=):\n");
        for (int i = 0; i < M; i++) {
            for (int j = 0; j <= N; j++) {
                scanf("%lf", &t[i][j]);
                fprintf(saveFp, "%.3lf ", t[i][j]);
            }
            fprintf(saveFp, "\n");
            basic[i] = N + i;
        }

        printf("Nhap he so ham muc tieu (dang MAX Z):\n");
        for (int j = 0; j < N; j++) {
            scanf("%lf", &t[M][j]);
            fprintf(saveFp, "%.3lf ", t[M][j]);
        }
        t[M][N] = 0;
        fprintf(saveFp, "%.3lf\n", t[M][N]);

        printTable(t, saveFp, choice);
        SimplexMethod(t, saveFp, choice);

        fprintf(saveFp, "\n== KET QUA CUOI CUNG ==\n");
        fprintf(saveFp, "Gia tri toi uu Z = %lf\n", -t[M][N]);

        for (int j = 0; j < N; j++) {
            double value = 0;
            for (int i = 0; i < M; i++) {
                if (basic[i] == j) {
                    value = t[i][N];
                    break;
                }
            }
            fprintf(saveFp, "x%d = %lf\n", j + 1, value);
        }
        fclose(saveFp);
        printf("\n== NOI DUNG FILE %s ==\n", saveFile);
        saveFp = fopen(saveFile, "r");
        if (saveFp != NULL) {
            DocFile(saveFp);
            fclose(saveFp);
        } else {
            printf("Khong the mo file %s\n", saveFile);
        }
    }

    return 0;
}
