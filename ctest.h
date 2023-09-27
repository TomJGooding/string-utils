#include <stdio.h>
#include <string.h>
#include <time.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define FAILURES_REPORT_SIZE 1024

static char failures_report[FAILURES_REPORT_SIZE];

static int tests_passed = 0;
static int tests_failed = 0;

static clock_t start_time = -1;

#define ctest_test_suite(suite_name) static void suite_name(void)

#define ctest_run_suite(suite_name) \
    do {                            \
        printf("%s ", #suite_name); \
        suite_name();               \
        printf("\n");               \
    } while (0)

#define ctest_report()                                                         \
    do {                                                                       \
        clock_t end_time = clock();                                            \
        double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;  \
        if (tests_failed > 0) {                                                \
            printf("%s", failures_report);                                     \
            printf(                                                            \
                (ANSI_COLOR_RED "%d failed " ANSI_COLOR_RESET), tests_failed   \
            );                                                                 \
        }                                                                      \
        if (tests_passed > 0) {                                                \
            printf(                                                            \
                (ANSI_COLOR_GREEN "%d passed " ANSI_COLOR_RESET), tests_passed \
            );                                                                 \
        }                                                                      \
        printf("in %0.2fs\n", time_taken);                                     \
    } while (0)

#define CTEST_EXIT_CODE tests_failed != 0

#define ctest_run_test(test)                               \
    do {                                                   \
        if (start_time == -1) {                            \
            start_time = clock();                          \
        }                                                  \
        int failed = test();                               \
        if (failed) {                                      \
            tests_failed++;                                \
            printf(ANSI_COLOR_RED "F" ANSI_COLOR_RESET);   \
        } else {                                           \
            tests_passed++;                                \
            printf(ANSI_COLOR_GREEN "." ANSI_COLOR_RESET); \
        }                                                  \
    } while (0)

#define ctest_assert(test)                                      \
    do {                                                        \
        if (!(test)) {                                          \
            snprintf(                                           \
                failures_report + strlen(failures_report),      \
                FAILURES_REPORT_SIZE - strlen(failures_report), \
                ANSI_COLOR_RED "FAILED " ANSI_COLOR_RESET       \
            );                                                  \
            snprintf(                                           \
                failures_report + strlen(failures_report),      \
                FAILURES_REPORT_SIZE - strlen(failures_report), \
                "%s::%s - Error: %s\n",                         \
                __FILE__,                                       \
                __func__,                                       \
                #test                                           \
            );                                                  \
            return 1;                                           \
        }                                                       \
    } while (0)
