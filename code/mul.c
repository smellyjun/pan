/*
 * Copyright 2020 Huawei Technologies Co., Ltd
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
二维矩阵计算，采用NEON指令优化
gcc -g multiply_simd.c -o multiply_simd
*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <arm_neon.h>

#define N    120
#define SEED    0x1234

//float *g_a, *g_b, *g_c;
float **g_a, **g_b, **g_c;

void gen_data(void)
{
    unsigned i,j;
    //g_a = (float*)malloc(N * sizeof(float));
    //g_b = (float*)malloc(N * sizeof(float));
    //g_c = (float*)malloc(N * sizeof(float));
    g_a=(float**)malloc(N * sizeof(float*));
    for(i=0;i<N;i++)
        g_a[i]=(float*)malloc(N * sizeof(float));
    g_b=(float**)malloc(N * sizeof(float*));
    for(i=0;i<N;i++)
        g_b[i]=(float*)malloc(N * sizeof(float));
    g_c=(float**)malloc(N * sizeof(float*));
    for(i=0;i<N;i++)
        g_c[i]=(float*)malloc(N * sizeof(float));

    if (g_a == NULL || g_b == NULL || g_c == NULL) {
        perror("Memory allocation through malloc failed");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < N; i++) {
        for(j=0;j<N;j++){
        // SEED * 0.1 is used to get duplicated random number
        g_a[i][j] = (float)(SEED * 0.1);
        g_b[i][j] = (float)(SEED * 0.1);
        }
    }
}

void free_data(void)
{
    //free(g_a);
    //free(g_b);
    //free(g_c);
    unsigned i;
    for(i=0;i<N;i++)free (g_a[i]);
    free (g_a);
    for(i=0;i<N;i++)free (g_b[i]);
    free (g_b);
    for(i=0;i<N;i++)free (g_c[i]);
    free (g_c);
}

void multiply(void)
{
    unsigned i,j,k;
    for (i = 0; i < N; i++) {
        for(j=0;j<N;j++){
            for(k=0;k<N;k++){
                g_c[i][j]+=g_a[i][k]*g_b[k][j];
            }
        }
    }
}
void multiply_neon(void){

    int i, j, k;
    float32x4_t src1, src2, dst;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < (N & ((~(unsigned)0x3))); k += 4) {
                src1 = vld1q_f32(g_a[i] + k);
                src2 = vld1q_f32(g_b[k] + j);
                dst = vmulq_f32(src1, src2);
                g_c[i][j] += vgetq_lane_f32(dst, 0) + vgetq_lane_f32(dst, 1) + vgetq_lane_f32(dst, 2) + vgetq_lane_f32(dst, 3);
            }

            for (; k < N; k++) {
                g_c[i][j] += g_a[i][k] * g_b[k][j];
            }
        }
    }
}
/*
void multiply_neon(void)
{
    int i;
    float32x4_t src1, src2, dst;

    for (i = 0; i < (N & ((~(unsigned)0x3))); i += 4) {
        src1 = vld1q_f32(g_a + i);
        src2 = vld1q_f32(g_b + i);
        dst = vmulq_f32(src1, src2);
        vst1q_f32(g_c + i, dst);
    }

    for (; i < N; i++) {
        g_c[i] = g_a[i] * g_b[i];
    }
}*/

void print_data(void)
{
    // print first 2 and last 2 element.
    printf("%f, %f, %f, %f\n", g_c[0][0], g_c[0][1], g_c[N - 1][N - 2], g_c[N - 1][N -1]);
}

int main(void)
{
    double msecs;
    struct timeval before, after;

    gen_data();
    gettimeofday(&before, NULL);
    multiply();
    //multiply_neon();
    gettimeofday(&after, NULL);

    // 1000 is used to convert tv_sec and tv_usec to msec.
    msecs = (after.tv_sec - before.tv_sec) * 1000.0 + (after.tv_usec - before.tv_usec) / 1000.0;
    print_data();
    printf("Execution time = %2.3lf ms\n", msecs);

    free_data();
    return 0;
}