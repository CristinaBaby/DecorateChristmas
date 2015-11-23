
#import "MakeFavItem.h"
#define kFavName @"FavName"

@implementation MakeFavItem
@synthesize favName=favName_;
- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}
-(id)initWithFavName:(NSString*)name type:(NSString*)type
{
    self = [super init];
    if (self) {
        // Initialization code here.
        self.favName=name;
        self.favType=type;
    }
    
    return self;
}
#pragma mark NSCoding

- (void) encodeWithCoder:(NSCoder *)encoder {
    
    [encoder encodeObject:favName_ forKey:kFavName];
}

- (id)initWithCoder:(NSCoder *)decoder {
    
    return [self initWithFavName:(NSString*)[decoder decodeObjectForKey:kFavName]type:@""];
}
-(void)dealloc
{
    [super dealloc];
}

@end
