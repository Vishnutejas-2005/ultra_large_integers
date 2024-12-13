#include "uint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uinteger_init(UInteger *num) {
    num->size = 1;
    num->digits = (int*)malloc(1 * sizeof(int));
    if (num->digits == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < 1; i++) {
        num->digits[i] = 0;
    }
    num->sign = 1; // Initially positive
}
void uinteger_free(UInteger *num) {
    free(num->digits);
}
void uinteger_resize(UInteger *num, int new_size) {
    num->digits = (int*)realloc(num->digits, new_size * sizeof(int));
    if (num->digits == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(1);
    }
    num->size = new_size;
    for (int i = num->size - 1; i >= new_size; i--) {
        num->digits[i] = 0;
    }
}
void uinteger_assign(UInteger *dest, const char *src) {
    int new_size;
    if (src[0] == '-'){
        if (strcmp(src,"-0")==0){
            dest->sign = 1;
            new_size = 1;
            uinteger_resize(dest, new_size);
            dest->digits[0] = 0;
            return;
        }
        dest->sign = -1;
        new_size = strlen(src) - 1;
        uinteger_resize(dest, new_size);

    } else {
        dest->sign = 1;
        new_size = strlen(src);
        uinteger_resize(dest, new_size);
    }
    for (int i = 0; i < new_size; i++) {
        dest->digits[i] = src[strlen(src)-i-1]-48;  

    }
    if(dest->digits[new_size-1]==-5){
      uinteger_resize(dest, new_size-1);
    }
}
int uinteger_scalar_compare(const UInteger *a,const UInteger *b){
    if (a->size > b->size){
        return 1;
    }else if (a->size < b->size){
        return -1;
    }else{
        for (int i = a->size - 1; i >= 0; i--) {
            if (a->digits[i] != b->digits[i]) {
                return ((a->digits[i] - b->digits[i])>0)?1:-1;
            }
        }
        return 0;
    }
}
int uinteger_compare(const UInteger *a, const UInteger *b) {
    if (a->sign != b->sign) {
        return a->sign; // Positive is greater than negative
    }
    if (a->size != b->size) {
        return ((a->sign * (a->size - b->size))>0)?1:-1;
    }
    int x = a->sign*(a->size - b->size);
    if (x>0) {
        return 1;
    } else if (x<0) {
        return -1;
    }else{
        for (int i = a->size - 1; i >= 0; i--) {
            if (a->digits[i] != b->digits[i]) {
                return ((a->sign * (a->digits[i] - b->digits[i]))>0)?1:-1;
            }
        }
        return 0;
    }

    return 0;
}
void remove_leading0(UInteger *x){
    if (x->digits[x->size-1]==0){
        int num=0;
        int i=x->size-1;
        while ((x->digits[i]==0) && (i>0)){
            num +=1;
            i-=1;
        }
        uinteger_resize(x,x->size-num);
    }
}
void add(UInteger *result, const UInteger *a, const UInteger *b) {
    int carry = 0;
    int max_size = (a->size > b->size) ? a->size : b->size;
    uinteger_resize(result, max_size);
    for (int i = 0; i < max_size || carry > 0; i++) {
        if (i == max_size){
            uinteger_resize(result, max_size+1);
            result->digits[i] = carry;
            break;
        }
        int sum = carry;
        if (i < a->size) {
            sum += a->digits[i];
        }
        if (i < b->size) {
            sum += b->digits[i];
        }
        result->digits[i] = sum % 10;
        carry = sum / 10;
    }
    // Adjust result size if there's no leading zero
    remove_leading0(result);
}
void subtract(UInteger *result, const UInteger *a, const UInteger *b) {
    int borrow = 0;
    uinteger_resize(result, a->size);
    for (int i = 0; i < a->size; i++) {
        int diff = a->digits[i] - borrow;
        if (i < b->size) {
            diff -= b->digits[i];
        }
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result->digits[i] = diff;
    }
    result->sign = 1;
    remove_leading0(result);
}
void uinteger_add(UInteger *result, const UInteger *a, const UInteger *b) {
    if (a->sign == b->sign){
        add(result, a, b);
        result->sign = a->sign;
    }
    else{
        int x = uinteger_scalar_compare(a, b);
        if (x > 0){
            subtract(result, a, b);
            result->sign = a->sign;
        }
        else if(x==0){
            uinteger_assign(result,"0");
        }
        else{
            subtract(result, b, a);
            result->sign = b->sign;
        }
    }
}

void uinteger_subtract(UInteger *result, const UInteger *a, const UInteger *b) {
    if (uinteger_compare(a, b) == 0){
        uinteger_assign(result,"0");
        return;
    }
    if (a->sign == b->sign&&a->sign==1) {
        if (uinteger_scalar_compare(a, b) < 0) {
            subtract(result, b, a);
            result->sign = -1;
        }
        else{
            subtract(result, a, b);
            result->sign = 1;
            }
    }
    else if (a->sign == b->sign&&a->sign==-1) {
        if (uinteger_scalar_compare(a, b) < 0) {
            subtract(result, b, a);
            result->sign = 1;
        }
        else{
            subtract(result, a, b);
            result->sign = -1;
    }
        remove_leading0(result);
    }
    else{
        // Different signs, perform addition
        add(result, a, b);
        result->sign = a->sign;
    }
}
// void uinteger_print(const UInteger *num) {
//     if (num->sign == -1) {
//         printf("-");
//     }
//     for (int i = num->size - 1; i >= 0; i--) {
//         printf("%d", num->digits[i]);
//     }
//     printf("\n");
// }
UInteger *create_uinteger_from_string(const char *str) {
    UInteger *num = (UInteger *)malloc(sizeof(UInteger));
    uinteger_init(num);
    uinteger_assign(num, str);
    return num;
}
void free_uinteger_list(UInteger **data, int n) {
    for (int i = 0; i < n; i++) {
        uinteger_free(data[i]);
        free(data[i]);
    }
    free(data);
}
int count_pairs(UInteger **data, int n, const UInteger *target) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            UInteger diff;
            uinteger_init(&diff);
            uinteger_subtract(&diff, data[i], data[j]);
            if (uinteger_compare(&diff, target) == 0) {
                count++;
            }
            uinteger_free(&diff);
        }
    }
    return count;
}
int open_file(char* filename){
    int n = 0;    
    int j = 0;
    int count = 0;
    UInteger *target = NULL;
    FILE *fp;
    char line[2500]; // Adjust buffer size as needed
    fp = fopen(filename, "r"); // Replace with your file name
    if (fp == NULL) {
        return -1;
    }
    if (fgets(line, sizeof(line), fp) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            if (len > 1 && line[len - 2] == '\r') {
                line[len - 2] = '\0';
            }
        }
        target = create_uinteger_from_string(line);
        remove_leading0(target);
    }
    if (fgets(line, sizeof(line), fp) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            if (len > 1 && line[len - 2] == '\r') {
                line[len - 2] = '\0';
            }
        }
        n = atoi(line);
    }
    UInteger **data = (UInteger **)malloc(n * sizeof(UInteger *));
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Remove trailing newline or carriage return
        size_t len = strlen(line);
        if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            if (len > 1 && line[len - 2] == '\r') {
                line[len - 2] = '\0';
            }
        }
        data[j] = create_uinteger_from_string(line);
        remove_leading0(data[j]);
        j++;
    }
    count =count_pairs(data, n, target);
    free_uinteger_list(data, n);
    uinteger_free(target);
    fclose(fp);
    return count;
}
