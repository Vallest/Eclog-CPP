#ifndef TESTS_H
#define TESTS_H

#import <UIKit/UIKit.h>

#if __cplusplus
    #define EXTERN extern "C"
#else
    #define EXTERN
#endif

EXTERN void runTestCasesAsync(UITextView* tv);

#endif // TESTS_H

