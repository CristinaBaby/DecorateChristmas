

#import <Foundation/Foundation.h>
/**搜藏的项目*/
@interface MakeFavItem : NSObject
{
    NSString *favName_;
}
/**收藏的名称*/
@property(nonatomic,retain)NSString *favName;
@property(nonatomic,retain)NSString *favType;
/**根据名称初始化 */
-(id)initWithFavName:(NSString*)name type:(NSString*)type;
@end
