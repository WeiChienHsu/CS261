//
//  main.c
//  Assignment1
//
//  Created by weichien on 28/06/2018.
//  Copyright © 2018 WeiChien. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int i;
    for(i = 0; i < argc; i++){
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}
