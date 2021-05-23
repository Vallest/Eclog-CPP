#import "ViewController.h"
#import "Tests.h"

@interface ViewController ()

@end

@implementation ViewController;

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.tv = [[UITextView alloc] init];

    self.tv.frame = CGRectMake(0, 44, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height - 88);
    
    self.tv.font = [UIFont fontWithName:@"Courier New" size:14];

    [self.view addSubview:self.tv];

    runTestCasesAsync(self.tv);
}

@end

