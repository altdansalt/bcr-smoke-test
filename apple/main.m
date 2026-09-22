#import <Foundation/Foundation.h>
#import "apple/ObjcGreeter.h"

int main(int argc, const char *argv[]) {
  @autoreleasepool {
    NSLog(@"%@", [[ObjcGreeter new] greet:@"BCR"]);
  }
  return 0;
}
