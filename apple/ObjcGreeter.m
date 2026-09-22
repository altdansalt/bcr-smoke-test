#import "apple/ObjcGreeter.h"
@implementation ObjcGreeter
- (NSString *)greet:(NSString *)name { return [NSString stringWithFormat:@"Hello, %@!", name]; }
@end
