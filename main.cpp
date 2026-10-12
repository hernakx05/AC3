1 #include <stdio.h>
2 #include <string.h>
3 #include "freertos/FreeRTOS.h"
4 #include "freertos/task.h"
5 #include "esp_log.h"
6
7 static const char *TAG = "matrix_calc";
8
9 void print_matrix(const char* name, float mat[2][2])
10 {
11 printf("%s:\n", name);
12 printf("[%7.2f, %7.2f]\n", mat[0][0], mat[0][1]);
13 printf("[%7.2f, %7.2f]\n\n", mat[1][0], mat[1][1]);
14 }
15
16 void read_serial_line(char* buffer, size_t max_len)
17 {
18 while (true) {
19 if (fgets(buffer, max_len, stdin) != NULL) {
20
21 buffer[strcspn(buffer, "\r")] = 0;
22 buffer[strcspn(buffer, "\n")] = 0;
23
24 if (strlen(buffer) > 0) {
25 return;
26 }
1
27 }
28
29 vTaskDelay(pdMS_TO_TICKS(50));
30 }
31 }
32
33 void app_main(void)
34 {
35 char rx_buffer[128];
36 float A[2][2], B[2][2], Res[2][2];
37
38 ESP_LOGI(TAG, "Operaciones Matriciales");
39
40 while (true) {
41 printf("A? a11 a12 a21 a22: \n");
42 read_serial_line(rx_buffer, sizeof(rx_buffer));
43 if (sscanf(rx_buffer, "%f %f %f %f", &A[0][0], &A[0][1], &A[1][0], &A
[1][1]) != 4) {
44 printf("Error.\n\n");
45 continue;
46 }
47
48 printf("B? b11 b12 b21 b22: \n");
49 read_serial_line(rx_buffer, sizeof(rx_buffer));
50 if (sscanf(rx_buffer, "%f %f %f %f", &B[0][0], &B[0][1], &B[1][0], &B
[1][1]) != 4) {
51 printf("Error.\n\n");
52 continue;
53 }
54
55 printf("\n---MATRICES---\n");
56 print_matrix("Matrix A", A);
57 print_matrix("Matrix B", B);
58
59 printf("---RESULTS---\n");
60
61 // 1. (A + B)
62 Res[0][0] = A[0][0] + B[0][0];
63 Res[0][1] = A[0][1] + B[0][1];
64 Res[1][0] = A[1][0] + B[1][0];
65 Res[1][1] = A[1][1] + B[1][1];
66 print_matrix("Addition (A + B)", Res);
67
68 printf("====================================\n\n");
69 }
70 }
