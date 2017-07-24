1、禁止手机睡眠

[UIApplication sharedApplication].idleTimerDisabled = YES;
2、隐藏某行cell

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    // 如果是你需要隐藏的那一行，返回高度为0
    if(indexPath.row == YouWantToHideRow)
        return 0;
    return 44;
}

// 然后再你需要隐藏cell的时候调用
[self.tableView beginUpdates];
[self.tableView endUpdates];
3、禁用button高亮

button.adjustsImageWhenHighlighted = NO;
或者在创建的时候
UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
4、tableview遇到这种报错failed to obtain a cell from its dataSource

是因为你的cell被调用的早了。先循环使用了cell，后又创建cell。顺序错了
可能原因：1、xib的cell没有注册 2、内存中已经有这个cell的缓存了(也就是说通过你的cellId找到的cell并不是你想要的类型)，这时候需要改下cell的标识
5、cocoa pods报这个错误：unable to access 'https://github.com/facebook/pop.git/': Operation timed out after 0 milliseconds with 0 out of 0 bytes received

解决办法：原因可能是网络问题，网络请求超时了，只需要重试就行了
6、cocoa pods 出现ERROR: While executing gem ... (Errno::EPERM)

解决办法：
https://segmentfault.com/q/1010000002926243
7、动画切换window的根控制器

// options是动画选项
[UIView transitionWithView:[UIApplication sharedApplication].keyWindow duration:0.5f options:UIViewAnimationOptionTransitionCrossDissolve animations:^{
    BOOL oldState = [UIView areAnimationsEnabled];
    [UIView setAnimationsEnabled:NO];
    [UIApplication sharedApplication].keyWindow.rootViewController = [RootViewController new];
    [UIView setAnimationsEnabled:oldState];
} completion:^(BOOL finished) {
    
}];
8、去除数组中重复的对象

NSArray *newArr = [oldArr valueForKeyPath:@"@distinctUnionOfObjects.self"];
9、编译的时候遇到 no such file or directory: ／users／apple／XXX是因为编译的时候，在此路径下找不到这个文件，解决这个问题，首先是是要检查缺少的文件是不是在工程中，如果不在工程中，需要从本地拖进去，如果发现已经存在工程中了，或者拖进去还是报错，这时候需要去build phases中搜索这个文件，这时候很可能会搜出现两个相同的文件，这时候，有一个路径是正确的，删除另外一个即可。如果删除了还是不行，需要把两个都删掉，然后重新往工程里拖进这个文件即可build phases
10、iOS8系统中，tableView最好实现下-tableView: heightForRowAtIndexPath:这个代理方法，要不然在iOS8中可能就会出现显示不全或者无法响应事件的问题
11、iOS8中实现侧滑功能的时候这个方法必须实现，要不然在iOS8中无法侧滑
                   
                   // 必须写的方法，和editActionsForRowAtIndexPath配对使用，里面什么不写也行
                   - (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
                       
                   }
12、三个通知NSSystemTimeZoneDidChangeNotification监听修改时间界面的两个按钮状态变化UIApplicationSignificantTimeChangeNotification 监听用户改变时间 （只要点击自动设置按钮就会调用） NSSystemClockDidChangeNotification 监听用户修改时间（时间不同才会调用）
13、SDWebImage本地缓存有时候会害人。如果之前缓存过一张图片，即使下次服务器换了这张图片，但是图片url没换，用sdwebimage下载下来的还是以前那张,所以遇到这种问题，不要先去怼服务器，清空下缓存再试就好了。
                   
14、上线前注意：
1）、删掉代码中所有的测试代码
2）、如果后台有审核模式，提醒后台开启此模式
3）、主流程再跑一跑
4）、全局搜索waring，检查所有标记waring的地方
15、跳进app权限设置
// 跳进app设置
                   if (UIApplicationOpenSettingsURLString != NULL) {
                       UIApplication *application = [UIApplication sharedApplication];
                       NSURL *URL = [NSURL URLWithString:UIApplicationOpenSettingsURLString];
                       if ([application respondsToSelector:@selector(openURL:options:completionHandler:)]) {
                           [application openURL:URL options:@{}
                              completionHandler:nil];
                       } else {
                           [application openURL:URL];
                       }
                   }
16、给一个view截图
                   
UIGraphicsBeginImageContextWithOptions(view.bounds.size, YES, 0.0);
[view.layer renderInContext:UIGraphicsGetCurrentContext()];
UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
UIGraphicsEndImageContext();
17、开发中如果要动态修改tableView的tableHeaderView或者tableFooterView的高度，需要给tableView重新设置，而不是直接更改高度。正确的做法是重新设置一下tableView.tableFooterView = 更改过高度的view。为什么？其实在iOS8以上直接改高度是没有问题的，在iOS8中出现了contentSize不准确的问题，这是解决办法。
                   
                   18、注意对象为nil的时候，调用此对象分类的方法不会执行
                   
                   19、collectionView的内容小于其宽高的时候是不能滚动的，设置可以滚动：
                   
                   collectionView.alwaysBounceHorizontal = YES;
                   collectionView.alwaysBounceVertical = YES;
                   20、设置navigationBar上的title颜色和大小
                   
                   [self.navigationController.navigationBar setTitleTextAttributes:@{NSForegroundColorAttributeName : [UIColor youColor], NSFontAttributeName : [UIFont systemFontOfSize:15]}]
                   21、颜色转图片
                   
                   + (UIImage *)cl_imageWithColor:(UIColor *)color {
                       CGRect rect = CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
                       UIGraphicsBeginImageContext(rect.size);
                       CGContextRef context = UIGraphicsGetCurrentContext();
                       
                       CGContextSetFillColorWithColor(context, [color CGColor]);
                       CGContextFillRect(context, rect);
                       
                       UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
                       UIGraphicsEndImageContext();
                       
                       return image;
                   }
                   22、view设置圆角
                   
#define ViewBorderRadius(View, Radius, Width, Color)\
\
[View.layer setCornerRadius:(Radius)];\
[View.layer setMasksToBounds:YES];\
[View.layer setBorderWidth:(Width)];\
[View.layer setBorderColor:[Color CGColor]] // view圆角
                   23、强／弱引用
                   
#define WeakSelf(type)  __weak typeof(type) weak##type = type; // weak
#define StrongSelf(type)  __strong typeof(type) type = weak##type; // strong
                   24、由角度转换弧度
                   
#define DegreesToRadian(x) (M_PI * (x) / 180.0)
                   25、由弧度转换角度
                   
#define RadianToDegrees(radian) (radian*180.0)/(M_PI)
                   26、获取图片资源
                   
#define GetImage(imageName) [UIImage imageNamed:[NSString stringWithFormat:@"%@",imageName]]
                   27、获取temp
                   
#define PathTemp NSTemporaryDirectory()
                   28、获取沙盒 Document
                   
#define PathDocument [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject]
                   29、获取沙盒 Cache
                   
#define PathCache [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) firstObject]
                   30、GCD代码只执行一次
                   
#define kDISPATCH_ONCE_BLOCK(onceBlock) static dispatch_once_t onceToken; dispatch_once(&onceToken, onceBlock);
                   31、自定义NSLog
                   
#ifdef DEBUG
#define NSLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define NSLog(...)
#endif
                   32、Font
                   
#define FontL(s)             [UIFont systemFontOfSize:s weight:UIFontWeightLight]
#define FontR(s)             [UIFont systemFontOfSize:s weight:UIFontWeightRegular]
#define FontB(s)             [UIFont systemFontOfSize:s weight:UIFontWeightBold]
#define FontT(s)             [UIFont systemFontOfSize:s weight:UIFontWeightThin]
#define Font(s)              FontL(s)
                   33、FORMAT
                   
#define FORMAT(f, ...)      [NSString stringWithFormat:f, ## __VA_ARGS__]
                   34、在主线程上运行
                   
#define kDISPATCH_MAIN_THREAD(mainQueueBlock) dispatch_async(dispatch_get_main_queue(), mainQueueBlock);
                   35、开启异步线程
                   
#define kDISPATCH_GLOBAL_QUEUE_DEFAULT(globalQueueBlock) dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), globalQueueBlocl);
                   36、通知
                   
#define NOTIF_ADD(n, f)     [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(f) name:n object:nil]
#define NOTIF_POST(n, o)    [[NSNotificationCenter defaultCenter] postNotificationName:n object:o]
#define NOTIF_REMV()        [[NSNotificationCenter defaultCenter] removeObserver:self]
                   37、随机颜色
                   
                   + (UIColor *)RandomColor {
                       NSInteger aRedValue = arc4random() % 255;
                       NSInteger aGreenValue = arc4random() % 255;
                       NSInteger aBlueValue = arc4random() % 255;
                       UIColor *randColor = [UIColor colorWithRed:aRedValue / 255.0f green:aGreenValue / 255.0f blue:aBlueValue / 255.0f alpha:1.0f];
                       return randColor;
                   }
                   38、获取window
                   
                   +(UIWindow*)getWindow {
                       UIWindow* win = nil; //[UIApplication sharedApplication].keyWindow;
                       for (id item in [UIApplication sharedApplication].windows) {
                           if ([item class] == [UIWindow class]) {
                               if (!((UIWindow*)item).hidden) {
                                   win = item;
                                   break;
                               }
                           }
                       }
                       return win;
                   }
                   39、修改textField的placeholder的字体颜色、大小
                   
                   [textField setValue:[UIColor redColor] forKeyPath:@"_placeholderLabel.textColor"];
                   [textField setValue:[UIFont boldSystemFontOfSize:16] forKeyPath:@"_placeholderLabel.font"];
                   40、统一收起键盘
                   
                   [[[UIApplication sharedApplication] keyWindow] endEditing:YES];
                   41、控制屏幕旋转，在控制器中写
                   
/** 是否支持自动转屏 */
                   - (BOOL)shouldAutorotate {
                       return YES;
                   }
                   
/** 支持哪些屏幕方向 */
                   - (UIInterfaceOrientationMask)supportedInterfaceOrientations {
                       return UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight;
                   }
                   
/** 默认的屏幕方向（当前ViewController必须是通过模态出来的UIViewController（模态带导航的无效）方式展现出来的，才会调用这个方法） */
                   - (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation {
                       return UIInterfaceOrientationLandscapeLeft | UIInterfaceOrientationLandscapeRight;
                   }
                   42、获取app缓存大小
                   
                   - (CGFloat)getCachSize {
                       
                       NSUInteger imageCacheSize = [[SDImageCache sharedImageCache] getSize];
                       //获取自定义缓存大小
                       //用枚举器遍历 一个文件夹的内容
                       //1.获取 文件夹枚举器
                       NSString *myCachePath = [NSHomeDirectory() stringByAppendingPathComponent:@"Library/Caches"];
                       NSDirectoryEnumerator *enumerator = [[NSFileManager defaultManager] enumeratorAtPath:myCachePath];
                       __block NSUInteger count = 0;
                       //2.遍历
                       for (NSString *fileName in enumerator) {
                           NSString *path = [myCachePath stringByAppendingPathComponent:fileName];
                           NSDictionary *fileDict = [[NSFileManager defaultManager] attributesOfItemAtPath:path error:nil];
                           count += fileDict.fileSize;//自定义所有缓存大小
                       }
                       // 得到是字节  转化为M
                       CGFloat totalSize = ((CGFloat)imageCacheSize+count)/1024/1024;
                       return totalSize;
                   }
                   43、清理app缓存
                   
                   - (void)handleClearView {
                       //删除两部分
                       //1.删除 sd 图片缓存
                       //先清除内存中的图片缓存
                       [[SDImageCache sharedImageCache] clearMemory];
                       //清除磁盘的缓存
                       [[SDImageCache sharedImageCache] clearDisk];
                       //2.删除自己缓存
                       NSString *myCachePath = [NSHomeDirectory() stringByAppendingPathComponent:@"Library/Caches"];
                       [[NSFileManager defaultManager] removeItemAtPath:myCachePath error:nil];
                   }
                   44、模型转字典
                   
                   static NSSet *classes;
                   
                   - (NSMutableDictionary *)getParameterDictionary {
                       
                       NSMutableDictionary *dict = [NSMutableDictionary dictionary];
                       
                       Class c = self.class;
                       
                       while (c) {
                           unsigned count;
                           objc_property_t *properties = class_copyPropertyList([c class], &count);
                           
                           for (int i = 0; i < count; i++) {
                               NSString *key = [NSString stringWithUTF8String:property_getName(properties[i])];
                               dict[key] = [self valueForKey:key];
                           }
                           free(properties);
                           
                           // 获得父类
                           c = class_getSuperclass(c);
                           
                           if ([self isClassFromFoundation:c]) break;
                       }
                       return dict;
                   }
                   
                   - (BOOL)isClassFromFoundation:(Class)c
{
    if (c == [NSObject class] || c == [NSManagedObject class]) return YES;
    
    __block BOOL result = NO;
    [[self foundationClasses] enumerateObjectsUsingBlock:^(Class foundationClass, BOOL *stop) {
        if ([c isSubclassOfClass:foundationClass]) {
            result = YES;
            *stop = YES;
        }
    }];
    return result;
}
                   
                   - (NSSet *)foundationClasses
{
    if (classes == nil) {
        // 集合中没有NSObject，因为几乎所有的类都是继承自NSObject，具体是不是NSObject需要特殊判断
        classes = [NSSet setWithObjects:
                   [NSURL class],
                   [NSDate class],
                   [NSValue class],
                   [NSData class],
                   [NSError class],
                   [NSArray class],
                   [NSDictionary class],
                   [NSString class],
                   [NSAttributedString class], nil];
    }
    return classes;
}
                   45、交换两个方法实现
                   
                   Class aClass = [self class];
                   
                   SEL originalSelector = @selector(viewWillAppear:);
                   SEL swizzledSelector = @selector(xxx_viewWillAppear:);
                   
                   Method originalMethod = class_getInstanceMethod(aClass, originalSelector);
                   Method swizzledMethod = class_getInstanceMethod(aClass, swizzledSelector);
                   
                   BOOL didAddMethod =
                   class_addMethod(aClass,
                                   originalSelector,
                                   method_getImplementation(swizzledMethod),
                                   method_getTypeEncoding(swizzledMethod));
                   
                   if (didAddMethod) {
                       class_replaceMethod(aClass,
                                           swizzledSelector,
                                           method_getImplementation(originalMethod),
                                           method_getTypeEncoding(originalMethod));
                   } else {
                       method_exchangeImplementations(originalMethod, swizzledMethod);
                   }
                   46、打印百分号和引号
                   
                   NSLog(@"%%");
                   NSLog(@"\"");
                   47、几个常用权限判断
                   
                   if ([CLLocationManager authorizationStatus] ==kCLAuthorizationStatusDenied) {
                       NSLog(@"没有定位权限");
                   }
                   AVAuthorizationStatus statusVideo = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
                   if (statusVideo == AVAuthorizationStatusDenied) {
                       NSLog(@"没有摄像头权限");
                   }
                   //是否有麦克风权限
                   AVAuthorizationStatus statusAudio = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];
                   if (statusAudio == AVAuthorizationStatusDenied) {
                       NSLog(@"没有录音权限");
                   }
                   [PHPhotoLibrary requestAuthorization:^(PHAuthorizationStatus status) {
    if (status == PHAuthorizationStatusDenied) {
        NSLog(@"没有相册权限");
    }
}];
                   48、获取手机型号
                   
                   + (NSString *)getDeviceInfo {
                       struct utsname systemInfo;
                       uname(&systemInfo);
                       NSString *platform = [NSString stringWithCString:systemInfo.machine encoding:NSASCIIStringEncoding];
                       if ([platform isEqualToString:@"iPhone1,1"]) return @"iPhone 2G";
                       if ([platform isEqualToString:@"iPhone1,2"]) return @"iPhone 3G";
                       if ([platform isEqualToString:@"iPhone2,1"]) return @"iPhone 3GS";
                       if ([platform isEqualToString:@"iPhone3,1"]) return @"iPhone 4";
                       if ([platform isEqualToString:@"iPhone3,2"]) return @"iPhone 4";
                       if ([platform isEqualToString:@"iPhone3,3"]) return @"iPhone 4";
                       if ([platform isEqualToString:@"iPhone4,1"]) return @"iPhone 4S";
                       if ([platform isEqualToString:@"iPhone5,1"]) return @"iPhone 5";
                       if ([platform isEqualToString:@"iPhone5,2"]) return @"iPhone 5";
                       if ([platform isEqualToString:@"iPhone5,3"]) return @"iPhone 5c";
                       if ([platform isEqualToString:@"iPhone5,4"]) return @"iPhone 5c";
                       if ([platform isEqualToString:@"iPhone6,1"]) return @"iPhone 5s";
                       if ([platform isEqualToString:@"iPhone6,2"]) return @"iPhone 5s";
                       if ([platform isEqualToString:@"iPhone7,1"]) return @"iPhone 6 Plus";
                       if ([platform isEqualToString:@"iPhone7,2"]) return @"iPhone 6";
                       if ([platform isEqualToString:@"iPhone8,1"]) return @"iPhone 6s";
                       if ([platform isEqualToString:@"iPhone8,2"]) return @"iPhone 6s Plus";
                       // 日行两款手机型号均为日本独占，可能使用索尼FeliCa支付方案而不是苹果支付
                       if ([platform isEqualToString:@"iPhone9,1"])    return @"国行、日版、港行iPhone 7";
                       if ([platform isEqualToString:@"iPhone9,2"])    return @"港行、国行iPhone 7 Plus";
                       if ([platform isEqualToString:@"iPhone9,3"])    return @"美版、台版iPhone 7";
                       if ([platform isEqualToString:@"iPhone9,4"])    return @"美版、台版iPhone 7 Plus";
                       if ([platform isEqualToString:@"iPhone8,4"]) return @"iPhone SE";
                       if ([platform isEqualToString:@"iPod1,1"]) return @"iPod Touch 1G";
                       if ([platform isEqualToString:@"iPod2,1"]) return @"iPod Touch 2G";
                       if ([platform isEqualToString:@"iPod3,1"]) return @"iPod Touch 3G";
                       if ([platform isEqualToString:@"iPod4,1"]) return @"iPod Touch 4G";
                       if ([platform isEqualToString:@"iPod5,1"]) return @"iPod Touch 5G";
                       if ([platform isEqualToString:@"iPad1,1"]) return @"iPad 1G";
                       if ([platform isEqualToString:@"iPad2,1"]) return @"iPad 2";
                       if ([platform isEqualToString:@"iPad2,2"]) return @"iPad 2";
                       if ([platform isEqualToString:@"iPad2,3"]) return @"iPad 2";
                       if ([platform isEqualToString:@"iPad2,4"]) return @"iPad 2";
                       if ([platform isEqualToString:@"iPad2,5"]) return @"iPad Mini 1G";
                       if ([platform isEqualToString:@"iPad2,6"]) return @"iPad Mini 1G";
                       if ([platform isEqualToString:@"iPad2,7"]) return @"iPad Mini 1G";
                       if ([platform isEqualToString:@"iPad3,1"]) return @"iPad 3";
                       if ([platform isEqualToString:@"iPad3,2"]) return @"iPad 3";
                       if ([platform isEqualToString:@"iPad3,3"]) return @"iPad 3";
                       if ([platform isEqualToString:@"iPad3,4"]) return @"iPad 4";
                       if ([platform isEqualToString:@"iPad3,5"]) return @"iPad 4";
                       if ([platform isEqualToString:@"iPad3,6"]) return @"iPad 4";
                       if ([platform isEqualToString:@"iPad4,1"]) return @"iPad Air";
                       if ([platform isEqualToString:@"iPad4,2"]) return @"iPad Air";
                       if ([platform isEqualToString:@"iPad4,3"]) return @"iPad Air";
                       if ([platform isEqualToString:@"iPad4,4"]) return @"iPad Mini 2G";
                       if ([platform isEqualToString:@"iPad4,5"]) return @"iPad Mini 2G";
                       if ([platform isEqualToString:@"iPad4,6"]) return @"iPad Mini 2G";
                       if ([platform isEqualToString:@"i386"]) return @"iPhone Simulator";
                       if ([platform isEqualToString:@"x86_64"]) return @"iPhone Simulator";
                       return platform;
                   }
                   49、长按复制功能
                   
                   - (void)viewDidLoad
{
    [self.view addGestureRecognizer:[[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(pasteBoard:)]];
}
                   - (void)pasteBoard:(UILongPressGestureRecognizer *)longPress {
                       if (longPress.state == UIGestureRecognizerStateBegan) {
                           UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
                           pasteboard.string = @"需要复制的文本";
                       }
                   }
                   50、cocoapods升级
                   
                   在终端执行 sudo gem install -n / usr / local / bin cocoapods --pre
                   51、设置启动页后，依然显示之前的
                   
                   删除app，手机重启，重新安装
                   52、判断图片类型
                   
                   //通过图片Data数据第一个字节 来获取图片扩展名
                   - (NSString *)contentTypeForImageData:(NSData *)data
{
    uint8_t c;
    [data getBytes:&c length:1];
    switch (c)
    {
        case 0xFF:
            return @"jpeg";
            
        case 0x89:
            return @"png";
            
        case 0x47:
            return @"gif";
            
        case 0x49:
        case 0x4D:
            return @"tiff";
            
        case 0x52:
            if ([data length] < 12) {
                return nil;
            }
            
            NSString *testString = [[NSString alloc] initWithData:[data subdataWithRange:NSMakeRange(0, 12)] encoding:NSASCIIStringEncoding];
            if ([testString hasPrefix:@"RIFF"]
                && [testString hasSuffix:@"WEBP"])
            {
                return @"webp";
            }
            
            return nil;
    }
    
    return nil;
}
                   53、获取手机和app信息
                   
                   NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
                   CFShow(infoDictionary);
                   // app名称
                   NSString *app_Name = [infoDictionary objectForKey:@"CFBundleDisplayName"];
                   // app版本
                   NSString *app_Version = [infoDictionary objectForKey:@"CFBundleShortVersionString"];
                   // app build版本
                   NSString *app_build = [infoDictionary objectForKey:@"CFBundleVersion"];
                   
                   
                   
                   //手机序列号
                   NSString* identifierNumber = [[UIDevice currentDevice] uniqueIdentifier];
                   NSLog(@"手机序列号: %@",identifierNumber);
                   //手机别名： 用户定义的名称
                   NSString* userPhoneName = [[UIDevice currentDevice] name];
                   NSLog(@"手机别名: %@", userPhoneName);
                   //设备名称
                   NSString* deviceName = [[UIDevice currentDevice] systemName];
                   NSLog(@"设备名称: %@",deviceName );
                   //手机系统版本
                   NSString* phoneVersion = [[UIDevice currentDevice] systemVersion];
                   NSLog(@"手机系统版本: %@", phoneVersion);
                   //手机型号
                   NSString* phoneModel = [[UIDevice currentDevice] model];
                   NSLog(@"手机型号: %@",phoneModel );
                   //地方型号  （国际化区域名称）
                   NSString* localPhoneModel = [[UIDevice currentDevice] localizedModel];
                   NSLog(@"国际化区域名称: %@",localPhoneModel );
                   
                   NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
                   // 当前应用名称
                   NSString *appCurName = [infoDictionary objectForKey:@"CFBundleDisplayName"];
                   NSLog(@"当前应用名称：%@",appCurName);
                   // 当前应用软件版本  比如：1.0.1
                   NSString *appCurVersion = [infoDictionary objectForKey:@"CFBundleShortVersionString"];
                   NSLog(@"当前应用软件版本:%@",appCurVersion);
                   // 当前应用版本号码   int类型
                   NSString *appCurVersionNum = [infoDictionary objectForKey:@"CFBundleVersion"];
                   NSLog(@"当前应用版本号码：%@",appCurVersionNum);
                   54、获取一个类的所有属性
                   
                   id LenderClass = objc_getClass("Lender");
                   unsigned int outCount, i;
                   objc_property_t *properties = class_copyPropertyList(LenderClass, &outCount);
                   for (i = 0; i < outCount; i++) {
                       objc_property_t property = properties[i];
                       fprintf(stdout, "%s %s\n", property_getName(property), property_getAttributes(property));
                   }
                   55、image圆角
                   
                   - (UIImage *)circleImage
{
    // NO代表透明
    UIGraphicsBeginImageContextWithOptions(self.size, NO, 1);
    // 获得上下文
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    // 添加一个圆
    CGRect rect = CGRectMake(0, 0, self.size.width, self.size.height);
    // 方形变圆形
    CGContextAddEllipseInRect(ctx, rect);
    // 裁剪
    CGContextClip(ctx);
    // 将图片画上去
    [self drawInRect:rect];
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}
                   56、image拉伸
                   
                   + (UIImage *)resizableImage:(NSString *)imageName
{
    UIImage *image = [UIImage imageNamed:imageName];
    CGFloat imageW = image.size.width;
    CGFloat imageH = image.size.height;
    return [image resizableImageWithCapInsets:UIEdgeInsetsMake(imageH * 0.5, imageW * 0.5, imageH * 0.5, imageW * 0.5) resizingMode:UIImageResizingModeStretch];
}
                   57、JSON字符串转字典
                   
                   + (NSDictionary *)parseJSONStringToNSDictionary:(NSString *)JSONString {
                       NSData *JSONData = [JSONString dataUsingEncoding:NSUTF8StringEncoding];
                       NSDictionary *responseJSON = [NSJSONSerialization JSONObjectWithData:JSONData options:NSJSONReadingMutableLeaves error:nil];
                       return responseJSON;
                   }
                   58、身份证号验证
                   
                   - (BOOL)validateIdentityCard {
                       BOOL flag;
                       if (self.length <= 0) {
                           flag = NO;
                           return flag;
                       }
                       NSString *regex2 = @"^(\\d{14}|\\d{17})(\\d|[xX])$";
                       NSPredicate *identityCardPredicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",regex2];
                       return [identityCardPredicate evaluateWithObject:self];
                   }
                   59、获取设备mac地址
                   
                   + (NSString *)macAddress {
                       int                 mib[6];
                       size_t              len;
                       char                *buf;
                       unsigned char       *ptr;
                       struct if_msghdr    *ifm;
                       struct sockaddr_dl  *sdl;
                       
                       mib[0] = CTL_NET;
                       mib[1] = AF_ROUTE;
                       mib[2] = 0;
                       mib[3] = AF_LINK;
                       mib[4] = NET_RT_IFLIST;
                       
                       if((mib[5] = if_nametoindex("en0")) == 0) {
                           printf("Error: if_nametoindex error\n");
                           return NULL;
                       }
                       
                       if(sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
                           printf("Error: sysctl, take 1\n");
                           return NULL;
                       }
                       
                       if((buf = malloc(len)) == NULL) {
                           printf("Could not allocate memory. Rrror!\n");
                           return NULL;
                       }
                       
                       if(sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
                           printf("Error: sysctl, take 2");
                           return NULL;
                       }
                       
                       ifm = (struct if_msghdr *)buf;
                       sdl = (struct sockaddr_dl *)(ifm + 1);
                       ptr = (unsigned char *)LLADDR(sdl);
                       NSString *outstring = [NSString stringWithFormat:@"%02X:%02X:%02X:%02X:%02X:%02X",
                                              *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
                       free(buf);
                       
                       return outstring;
                   }
                   60、导入自定义字体库
                   
                   1、找到你想用的字体的 ttf 格式，拖入工程
                   2、在工程的plist中增加一行数组，“Fonts provided by application”
                   3、为这个key添加一个item，value为你刚才导入的ttf文件名
                   4、直接使用即可：label.font = [UIFont fontWithName:@"你刚才导入的ttf文件名" size:20.0]；
                   61、拿到当前正在显示的控制器，不管是push进去的，还是present进去的都能拿到
                   
                   - (UIViewController *)getVisibleViewControllerFrom:(UIViewController*)vc {
                       if ([vc isKindOfClass:[UINavigationController class]]) {
                           return [self getVisibleViewControllerFrom:[((UINavigationController*) vc) visibleViewController]];
                       }else if ([vc isKindOfClass:[UITabBarController class]]){
                           return [self getVisibleViewControllerFrom:[((UITabBarController*) vc) selectedViewController]];
                       } else {
                           if (vc.presentedViewController) {
                               return [self getVisibleViewControllerFrom:vc.presentedViewController];
                           } else {
                               return vc;
                           }
                       }
                   }
                   62、runtime为一个类动态添加属性
                   
                   // 动态添加属性的本质是: 让对象的某个属性与值产生关联
                   objc_setAssociatedObject(self, WZBPlaceholderViewKey, placeholderView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
                   63、获取runtime为一个类动态添加的属性
                   
                   objc_getAssociatedObject(self, WZBPlaceholderViewKey);
                   64、KVO监听某个对象的属性
                   
                   // 添加监听者
                   [self addObserver:self forKeyPath:property options:NSKeyValueObservingOptionNew context:nil];
                   
                   // 当监听的属性值变化的时候会来到这个方法
                   - (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
                       if ([keyPath isEqualToString:@"property"]) {
                           [self textViewTextChange];
                       } else {
                       }
                   }
                   65、Reachability判断网络状态
                   
                   NetworkStatus status = [[Reachability reachabilityForInternetConnection] currentReachabilityStatus];
                   if (status == NotReachable) {
                       NSLog(@"当前设备无网络");
                   }
                   if (status == ReachableViaWiFi) {
                       NSLog(@"当前wifi网络");
                   }
                   if (status == ReachableViaWWAN) {
                       NSLog(@"当前蜂窝移动网络");
                   }
                   66、AFNetworking监听网络状态
                   
                   // 监听网络状况
                   AFNetworkReachabilityManager *mgr = [AFNetworkReachabilityManager sharedManager];
                   [mgr setReachabilityStatusChangeBlock:^(AFNetworkReachabilityStatus status) {
    switch (status) {
        case AFNetworkReachabilityStatusUnknown:
            break;
        case AFNetworkReachabilityStatusNotReachable: {
            [SVProgressHUD showInfoWithStatus:@"当前设备无网络"];
        }
            break;
        case AFNetworkReachabilityStatusReachableViaWiFi:
            [SVProgressHUD showInfoWithStatus:@"当前Wi-Fi网络"];
            break;
        case AFNetworkReachabilityStatusReachableViaWWAN:
            [SVProgressHUD showInfoWithStatus:@"当前蜂窝移动网络"];
            break;
        default:
            break;
    }
}];
                   [mgr startMonitoring];
                   67、透明颜色不影响子视图透明度
                   
                   [UIColor colorWithRed:<#(CGFloat)#> green:<#(CGFloat)#> blue:<#(CGFloat)#> alpha:<#(CGFloat)#>];
                   68、取图片某一点的颜色
                   
                   if (point.x < 0 || point.y < 0) return nil;
                   
                   CGImageRef imageRef = self.CGImage;
                   NSUInteger width = CGImageGetWidth(imageRef);
                   NSUInteger height = CGImageGetHeight(imageRef);
                   if (point.x >= width || point.y >= height) return nil;
                   
                   unsigned char *rawData = malloc(height * width * 4);
                   if (!rawData) return nil;
                   
                   CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
                   NSUInteger bytesPerPixel = 4;
                   NSUInteger bytesPerRow = bytesPerPixel * width;
                   NSUInteger bitsPerComponent = 8;
                   CGContextRef context = CGBitmapContextCreate(rawData,
                                                                width,
                                                                height,
                                                                bitsPerComponent,
                                                                bytesPerRow,
                                                                colorSpace,
                                                                kCGImageAlphaPremultipliedLast
                                                                | kCGBitmapByteOrder32Big);
                   if (!context) {
                       free(rawData);
                       return nil;
                   }
                   CGColorSpaceRelease(colorSpace);
                   CGContextDrawImage(context, CGRectMake(0, 0, width, height), imageRef);
                   CGContextRelease(context);
                   
                   int byteIndex = (bytesPerRow * point.y) + point.x * bytesPerPixel;
                   CGFloat red   = (rawData[byteIndex]     * 1.0) / 255.0;
                   CGFloat green = (rawData[byteIndex + 1] * 1.0) / 255.0;
                   CGFloat blue  = (rawData[byteIndex + 2] * 1.0) / 255.0;
                   CGFloat alpha = (rawData[byteIndex + 3] * 1.0) / 255.0;
                   
                   UIColor *result = nil;
                   result = [UIColor colorWithRed:red green:green blue:blue alpha:alpha];
                   free(rawData);
                   return result;
                   69、判断该图片是否有透明度通道
                   
                   - (BOOL)hasAlphaChannel
{
    CGImageAlphaInfo alpha = CGImageGetAlphaInfo(self.CGImage);
    return (alpha == kCGImageAlphaFirst ||
            alpha == kCGImageAlphaLast ||
            alpha == kCGImageAlphaPremultipliedFirst ||
            alpha == kCGImageAlphaPremultipliedLast);
}
                   70、获得灰度图
                   
                   + (UIImage*)covertToGrayImageFromImage:(UIImage*)sourceImage
{
    int width = sourceImage.size.width;
    int height = sourceImage.size.height;
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceGray();
    CGContextRef context = CGBitmapContextCreate (nil,width,height,8,0,colorSpace,kCGImageAlphaNone);
    CGColorSpaceRelease(colorSpace);
    
    if (context == NULL) {
        return nil;
    }
    
    CGContextDrawImage(context,CGRectMake(0, 0, width, height), sourceImage.CGImage);
    CGImageRef contextRef = CGBitmapContextCreateImage(context);
    UIImage *grayImage = [UIImage imageWithCGImage:contextRef];
    CGContextRelease(context);
    CGImageRelease(contextRef);
    
    return grayImage;
}
                   71、根据bundle中的文件名读取图片
                   
                   + (UIImage *)imageWithFileName:(NSString *)name {
                       NSString *extension = @"png";
                       
                       NSArray *components = [name componentsSeparatedByString:@"."];
                       if ([components count] >= 2) {
                           NSUInteger lastIndex = components.count - 1;
                           extension = [components objectAtIndex:lastIndex];
                           
                           name = [name substringToIndex:(name.length-(extension.length+1))];
                       }
                       
                       // 如果为Retina屏幕且存在对应图片，则返回Retina图片，否则查找普通图片
                       if ([UIScreen mainScreen].scale == 2.0) {
                           name = [name stringByAppendingString:@"@2x"];
                           
                           NSString *path = [[NSBundle mainBundle] pathForResource:name ofType:extension];
                           if (path != nil) {
                               return [UIImage imageWithContentsOfFile:path];
                           }
                       }
                       
                       if ([UIScreen mainScreen].scale == 3.0) {
                           name = [name stringByAppendingString:@"@3x"];
                           
                           NSString *path = [[NSBundle mainBundle] pathForResource:name ofType:extension];
                           if (path != nil) {
                               return [UIImage imageWithContentsOfFile:path];
                           }
                       }
                       
                       NSString *path = [[NSBundle mainBundle] pathForResource:name ofType:extension];
                       if (path) {
                           return [UIImage imageWithContentsOfFile:path];
                       }
                       
                       return nil;
                   }
                   72、合并两个图片
                   
                   + (UIImage*)mergeImage:(UIImage*)firstImage withImage:(UIImage*)secondImage {
                       CGImageRef firstImageRef = firstImage.CGImage;
                       CGFloat firstWidth = CGImageGetWidth(firstImageRef);
                       CGFloat firstHeight = CGImageGetHeight(firstImageRef);
                       CGImageRef secondImageRef = secondImage.CGImage;
                       CGFloat secondWidth = CGImageGetWidth(secondImageRef);
                       CGFloat secondHeight = CGImageGetHeight(secondImageRef);
                       CGSize mergedSize = CGSizeMake(MAX(firstWidth, secondWidth), MAX(firstHeight, secondHeight));
                       UIGraphicsBeginImageContext(mergedSize);
                       [firstImage drawInRect:CGRectMake(0, 0, firstWidth, firstHeight)];
                       [secondImage drawInRect:CGRectMake(0, 0, secondWidth, secondHeight)];
                       UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
                       UIGraphicsEndImageContext();
                       return image;
                   }
                   73、根据bundle中的图片名创建imageview
                   
                   + (id)imageViewWithImageNamed:(NSString*)imageName
{
    return [[UIImageView alloc] initWithImage:[UIImage imageNamed:imageName]];
}
                   74、为imageView添加倒影
                   
                   CGRect frame = self.frame;
                   frame.origin.y += (frame.size.height + 1);
                   
                   UIImageView *reflectionImageView = [[UIImageView alloc] initWithFrame:frame];
                   self.clipsToBounds = TRUE;
                   reflectionImageView.contentMode = self.contentMode;
                   [reflectionImageView setImage:self.image];
                   reflectionImageView.transform = CGAffineTransformMakeScale(1.0, -1.0);
                   
                   CALayer *reflectionLayer = [reflectionImageView layer];
                   
                   CAGradientLayer *gradientLayer = [CAGradientLayer layer];
                   gradientLayer.bounds = reflectionLayer.bounds;
                   gradientLayer.position = CGPointMake(reflectionLayer.bounds.size.width / 2, reflectionLayer.bounds.size.height * 0.5);
                   gradientLayer.colors = [NSArray arrayWithObjects:
                                           (id)[[UIColor clearColor] CGColor],
                                           (id)[[UIColor colorWithRed:1.0 green:1.0 blue:1.0 alpha:0.3] CGColor], nil];
                   
                   gradientLayer.startPoint = CGPointMake(0.5,0.5);
                   gradientLayer.endPoint = CGPointMake(0.5,1.0);
                   reflectionLayer.mask = gradientLayer;
                   
                   [self.superview addSubview:reflectionImageView];
                   75、画水印
                   
                   // 画水印
                   - (void) setImage:(UIImage *)image withWaterMark:(UIImage *)mark inRect:(CGRect)rect
{
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 4.0)
    {
        UIGraphicsBeginImageContextWithOptions(self.frame.size, NO, 0.0);
    }
    //原图
    [image drawInRect:self.bounds];
    //水印图
    [mark drawInRect:rect];
    UIImage *newPic = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    self.image = newPic;
}
                   76、让label的文字内容显示在左上／右上／左下／右下／中心顶／中心底部
                   
                   自定义UILabel
                   // 重写label的textRectForBounds方法
                   - (CGRect)textRectForBounds:(CGRect)bounds limitedToNumberOfLines:(NSInteger)numberOfLines {
                       CGRect rect = [super textRectForBounds:bounds limitedToNumberOfLines:numberOfLines];
                       switch (self.textAlignmentType) {
                           case WZBTextAlignmentTypeLeftTop: {
                               rect.origin = bounds.origin;
                           }
                               break;
                           case WZBTextAlignmentTypeRightTop: {
                               rect.origin = CGPointMake(CGRectGetMaxX(bounds) - rect.size.width, bounds.origin.y);
                           }
                               break;
                           case WZBTextAlignmentTypeLeftBottom: {
                               rect.origin = CGPointMake(bounds.origin.x, CGRectGetMaxY(bounds) - rect.size.height);
                           }
                               break;
                           case WZBTextAlignmentTypeRightBottom: {
                               rect.origin = CGPointMake(CGRectGetMaxX(bounds) - rect.size.width, CGRectGetMaxY(bounds) - rect.size.height);
                           }
                               break;
                           case WZBTextAlignmentTypeTopCenter: {
                               rect.origin = CGPointMake((CGRectGetWidth(bounds) - CGRectGetWidth(rect)) / 2, CGRectGetMaxY(bounds) - rect.origin.y);
                           }
                               break;
                           case WZBTextAlignmentTypeBottomCenter: {
                               rect.origin = CGPointMake((CGRectGetWidth(bounds) - CGRectGetWidth(rect)) / 2, CGRectGetMaxY(bounds) - CGRectGetMaxY(bounds) - rect.size.height);
                           }
                               break;
                           case WZBTextAlignmentTypeLeft: {
                               rect.origin = CGPointMake(0, rect.origin.y);
                           }
                               break;
                           case WZBTextAlignmentTypeRight: {
                               rect.origin = CGPointMake(rect.origin.x, 0);
                           }
                               break;
                           case WZBTextAlignmentTypeCenter: {
                               rect.origin = CGPointMake((CGRectGetWidth(bounds) - CGRectGetWidth(rect)) / 2, (CGRectGetHeight(bounds) - CGRectGetHeight(rect)) / 2);
                           }
                               break;
                               
                           default:
                               break;
                       }
                       return rect;
                   }
                   - (void)drawTextInRect:(CGRect)rect {
                       CGRect textRect = [self textRectForBounds:rect limitedToNumberOfLines:self.numberOfLines];
                       [super drawTextInRect:textRect];
                   }
                   77、scrollView上的输入框，键盘挡住的问题
                   
                   推荐用IQKeyboardManager这个框架！
                   手动解决如下
                   1、监听键盘弹出／消失的通知
                   2、在通知中加入代码：
                   NSDictionary* info = [aNotification userInfo];
                   CGRect keyPadFrame=[[UIApplication sharedApplication].keyWindow convertRect:[[info objectForKey:UIKeyboardFrameBeginUserInfoKey] CGRectValue] fromView:self.view];
                   CGSize kbSize =keyPadFrame.size;
                   CGRect activeRect=[self.view convertRect:activeField.frame fromView:activeField.superview];
                   CGRect aRect = self.view.bounds;
                   aRect.size.height -= (kbSize.height);
                   
                   CGPoint origin =  activeRect.origin;
                   origin.y -= backScrollView.contentOffset.y;
                   if (!CGRectContainsPoint(aRect, origin)) {
                       CGPoint scrollPoint = CGPointMake(0.0,CGRectGetMaxY(activeRect)-(aRect.size.height));
                       [backScrollView setContentOffset:scrollPoint animated:YES];
                   }
                   78、frame布局的cell动态高度
                   
                   这种通常在你的模型中添加一个辅助属性cellHeight，在模型中重写这个属性的get方法，根据你的布局和模型中的其他属性值计算出总高度。最后在tableView：heightForRow方法中，根据indexPath找出对应的模型，返回这个高度即可。
                   79、AutoLayout布局的cell动态高度
                   
                   // 1、设置tableView的属性
                   self.tableView.rowHeight = UITableViewAutomaticDimension;
                   self.tableView.estimatedRowHeight = 44.0; // 这个属性非0，估计cell高度
                   // 2、至上而下设置cell的约束，注意，上下左右最好都要顶到cell的四周
                   
                   cell
                   80、使用performSelector:调用函数，内存泄漏问题
                   
                   当我们在开发中使用[obj performSelector:NSSelectorFromString(@"aMethod")];这类方法时可能会收到一个警告"performSelector may cause a leak because its selector is unknown".
                   是因为编译器不清楚这个对象能不能相应这个方法，如果不能，则是不安全的，而且编译器也不清楚该怎么处理这个方法的返回值！
                   使用以下代码调用即可：
                   if (! obj) { return; }
                   SEL selector = NSSelectorFromString(@"aMethod");
                   IMP imp = [obj methodForSelector:selector];
                   void (*func)(id, SEL) = (void *)imp;
                   func(obj, selector);
                   
                   或者：
                   SEL selector = NSSelectorFromString(@"aMethod");
                   ((void (*)(id, SEL))[obj methodForSelector:selector])(obj, selector);
                   81、一个字符串是否包含另一个字符串
                   
                   // 方法1
                   if ([str1 containsString:str2]) {
                       NSLog(@"str1包含str2");
                   } else {
                       NSLog(@"str1不包含str2");
                   }
                   
                   // 方法2
                   if ([str1 rangeOfString: str2].location == NSNotFound) {
                       NSLog(@"str1不包含str2");
                   } else {
                       NSLog(@"str1包含str2");
                   }
                   82、cell去除选中效果
                   
                   cell.selectionStyle = UITableViewCellSelectionStyleNone;
                   83、cell点按效果
                   
                   - (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
                       [tableView deselectRowAtIndexPath:indexPath animated:YES];
                   }
                   84、当删除一个从xib拖出来的属性时，一定记得把xib中对应的线也删掉，不然会报类似[<ViewController 0x7fea6ed05980> setValue:forUndefinedKey:]: this class is not key value coding-compliant for the key的crash
                   
                   
                   点击这个叉号删除
                   85、真机测试的时候报错：Could not launch "你的 App"，process launch failed: Security
                   
                   因为你的app没有上线，iOS9开始，需要手动信任Xcode生成的描述文件，打开手机设置->通用->描述文件->点击你的app的描述文件->点击信任
                   86、真机测试的时候报错：Could not find Developer Disk Image
                   
                   这是因为你的设备系统版本大于Xcode能兼容的系统版本，比如你的设备是iOS10.3，而Xcode版本是8.2（Xcode8.2最大兼容iOS10.2），就会报这个错误。解决办法就是升级Xcode！
                   87、UITextView没有placeholder的问题？
                   
                   网上有很多此类自定义控件，也可以参考下我写的一个UITextView分类 UITextView-WZB
                   88、移除字符串中的空格和换行
                   
                   + (NSString *)removeSpaceAndNewline:(NSString *)str {
                       NSString *temp = [str stringByReplacingOccurrencesOfString:@" " withString:@""];
                       temp = [temp stringByReplacingOccurrencesOfString:@"\r" withString:@""];
                       temp = [temp stringByReplacingOccurrencesOfString:@"\n" withString:@""];
                       return temp;
                   }
                   89、判断字符串中是否有空格
                   
                   + (BOOL)isBlank:(NSString *)str {
                       NSRange _range = [str rangeOfString:@" "];
                       if (_range.location != NSNotFound) {
                           //有空格
                           return YES;
                       } else {
                           //没有空格
                           return NO;
                       }
                   }
                   90、获取一个视频的第一帧图片
                   
                   NSURL *url = [NSURL URLWithString:filepath];
                   AVURLAsset *asset1 = [[AVURLAsset alloc] initWithURL:url options:nil];
                   AVAssetImageGenerator *generate1 = [[AVAssetImageGenerator alloc] initWithAsset:asset1];
                   generate1.appliesPreferredTrackTransform = YES;
                   NSError *err = NULL;
                   CMTime time = CMTimeMake(1, 2);
                   CGImageRef oneRef = [generate1 copyCGImageAtTime:time actualTime:NULL error:&err];
                   UIImage *one = [[UIImage alloc] initWithCGImage:oneRef];
                   
                   return one;
                   91、获取视频的时长
                   
                   + (NSInteger)getVideoTimeByUrlString:(NSString *)urlString {
                       NSURL *videoUrl = [NSURL URLWithString:urlString];
                       AVURLAsset *avUrl = [AVURLAsset assetWithURL:videoUrl];
                       CMTime time = [avUrl duration];
                       int seconds = ceil(time.value/time.timescale);
                       return seconds;
                   }
                   92、字符串是否为空
                   
                   + (BOOL)isEqualToNil:(NSString *)str {
                       return str.length <= 0 || [str isEqualToString:@""] || !str;
                   }
                   93、将app上传到App Store的时候通常会遇到这个问题
                   
                   
                   try again
                   很多人说这事苹果爸爸服务器问题，重复尝试几次，总会成功的！
                   但是经过尝试发现如果使用Application Loader上传成功率就非常高，所以还是推荐把ipa文件导出直接用Application Loader上传。
                   如果Application Loader也不行，需要检查下自己的网络，有时候vpn也会提高速度。
                   94、当tableView占不满一屏时，去除下边多余的单元格
                   
                   self.tableView.tableHeaderView = [UIView new];
                   self.tableView.tableFooterView = [UIView new];
                   95、isKindOfClass和isMemberOfClass的区别
                   
                   isKindOfClass可以判断某个对象是否属于某个类，或者这个类的子类。
                   isMemberOfClass更加精准，它只能判断这个对象类型是否为这个类(不能判断子类)
                   96、__block
                   
                   当一个局部变量需要在block里改变时，需要在定义时加上__block修饰，具体请看官方文档 http://developer.apple.com/library/ios/documentation/cocoa/Conceptual/Blocks/Articles/bxVariables.html#//apple_ref/doc/uid/TP40007502-CH6-SW6
                   97、-[ViewController aMethod:]: unrecognized selector sent to instance 0x7fe91e607fb0
                   
                   这是一个经典错误，ViewController不能响应aMethod这个方法，错误原因可能viewController文件中没有实现aMethod这个方法
                   98、UITableView (<UITableView: 0x7ff19b027000; >) failed to obtain a cell from its dataSource (<ViewController: 0x7ff19a507520>)
                   
                   这个错误原因是tableView的代理方法-tableView:cellForRowAtIndexPath:需要返回一个UITableViewCell,而你返回了一个nil。另外这个地方返回值不是UITableViewCell类型也会导致崩溃
                   99、约束如何做UIView动画？
                   
                   1、把需要改的约束Constraint拖条线出来，成为属性
                   2、在需要动画的地方加入代码，改变此属性的constant属性
                   3、开始做UIView动画，动画里边调用layoutIfNeeded方法
                   
                   @property (weak, nonatomic) IBOutlet NSLayoutConstraint *buttonTopConstraint;
                   self.buttonTopConstraint.constant = 100;
                   [UIView animateWithDuration:.5 animations:^{
    [self.view layoutIfNeeded];
}];
                   100、从NSURL中拿到链接字符串
                   
                   NSString *urlString = myURL.absoluteString;
                   101、将tableView滚动到顶部
                   
                   [tableView setContentOffset:CGPointZero animated:YES];
                   或者
                   [tableView scrollRectToVisible:CGRectMake(0, 0, 1, 1) animated:YES];
                   102、如果用addTarget:action:forControlEvents:方法为一个button添加了很多点击事件，在某个时刻想一次删除怎么办？只需要调用下边这句代码
                   
                   [youButton removeTarget:nil action:nil forControlEvents:UIControlEventAllEvents];
                   103、某个字体的高度
                   
                   font.lineHeight;
                   104、删除某个view所有的子视图
                   
                   [[someView subviews]
                    makeObjectsPerformSelector:@selector(removeFromSuperview)];
                   105、删除NSUserDefaults所有记录
                   
                   //方法一
                   NSString *appDomain = [[NSBundle mainBundle] bundleIdentifier];
                   [[NSUserDefaults standardUserDefaults] removePersistentDomainForName:appDomain];
                   //方法二
                   - (void)resetDefaults {
                       NSUserDefaults * defs = [NSUserDefaults standardUserDefaults];
                       NSDictionary * dict = [defs dictionaryRepresentation];
                       for (id key in dict) {
                           [defs removeObjectForKey:key];
                       }
                       [defs synchronize];
                   }
                   // 方法三
                   [[NSUserDefaults standardUserDefaults] setPersistentDomain:[NSDictionary dictionary] forName:[[NSBundle mainBundle] bundleIdentifier]];
                   106、禁用系统滑动返回功能
                   
                   - (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    if ([self.navigationController respondsToSelector:@selector(interactivePopGestureRecognizer)]) {self.navigationController.interactivePopGestureRecognizer.delegate = self;
    }
}
                   
                   - (void)viewWillDisappear:(BOOL)animated {
                       [super viewWillDisappear:animated];
                       if ([self.navigationController respondsToSelector:@selector(interactivePopGestureRecognizer)]) {self.navigationController.interactivePopGestureRecognizer.delegate = nil;
                       }
                   }
                   - (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    return NO;
}
                   107、模拟器报错
                   
                   
                   模拟器报错
                   解决办法：
                   打开模拟器->Simulator->Reset Content and Settings...
                   如果不行，就重启试试！
                   108、自定义cell选中背景颜色
                   
                   UIView *bgColorView = [[UIView alloc] init];
                   bgColorView.backgroundColor = [UIColor redColor];
                   [cell setSelectedBackgroundView:bgColorView];
                   109、UILabel设置内边距
                   
                   子类化UILabel，重写drawTextInRect方法
                   - (void)drawTextInRect:(CGRect)rect {
                       // 边距，上左下右
                       UIEdgeInsets insets = {0, 5, 0, 5};
                       [super drawTextInRect:UIEdgeInsetsInsetRect(rect, insets)];
                   }
                   110、UILabel设置文字描边
                   
                   子类化UILabel，重写drawTextInRect方法
                   - (void)drawTextInRect:(CGRect)rect
{
    CGContextRef c = UIGraphicsGetCurrentContext();
    // 设置描边宽度
    CGContextSetLineWidth(c, 1);
    CGContextSetLineJoin(c, kCGLineJoinRound);
    CGContextSetTextDrawingMode(c, kCGTextStroke);
    // 描边颜色
    self.textColor = [UIColor redColor];
    [super drawTextInRect:rect];
    // 文本颜色
    self.textColor = [UIColor yellowColor];
    CGContextSetTextDrawingMode(c, kCGTextFill);
    [super drawTextInRect:rect];
}
                   111、使用模拟器截图
                   
                   快捷键command + s
                   或者File->Save Screen Shot
                   112、scrollView滚动到最下边
                   
                   CGPoint bottomOffset = CGPointMake(0, scrollView.contentSize.height - scrollView.bounds.size.height);
                   [scrollView setContentOffset:bottomOffset animated:YES];
                   113、UIView背景颜色渐变
                   
                   UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 320, 100)];
                   [self.view addSubview:view];
                   CAGradientLayer *gradient = [CAGradientLayer layer];
                   gradient.frame = view.bounds;
                   gradient.colors = [NSArray arrayWithObjects:(id)[[UIColor blackColor] CGColor], (id)[[UIColor whiteColor] CGColor], nil];
                   [view.layer insertSublayer:gradient atIndex:0];
                   114、停止UIView动画
                   
                   [yourView.layer removeAllAnimations]
                   115、为UIView某个角添加圆角
                   
                   // 左上角和右下角添加圆角
                   UIBezierPath *maskPath = [UIBezierPath bezierPathWithRoundedRect:view.bounds byRoundingCorners:(UIRectCornerTopLeft | UIRectCornerBottomRight) cornerRadii:CGSizeMake(20, 20)];
                   CAShapeLayer *maskLayer = [CAShapeLayer layer];
                   maskLayer.frame = view.bounds;
                   maskLayer.path = maskPath.CGPath;
                   view.layer.mask = maskLayer;
                   116、删除Xcode Derived data缓存数据
                   
                   依次点击Xcode -> Preferences -> location，然后点击 Derived data路径后到小箭头，删除这个文件夹下的数据就可以了，如图
                   
                   
                   Xcode Derived data
                   117、将一个view放置在其兄弟视图的最上面
                   
                   [parentView bringSubviewToFront:yourView]
                   118、将一个view放置在其兄弟视图的最下面
                   
                   [parentView sendSubviewToBack:yourView]
                   119、让手机震动一下
                   
                   倒入框架
#import <AudioToolbox/AudioToolbox.h>
                   AudioServicesPlayAlertSound(kSystemSoundID_Vibrate);
                   或者
                   AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
                   120、layoutSubviews方法什么时候调用？
                   
                   1、init方法不会调用
                   2、addSubview方法等时候会调用
                   3、bounds改变的时候调用
                   4、scrollView滚动的时候会调用scrollView的layoutSubviews方法(所以不建议在scrollView的layoutSubviews方法中做复杂逻辑)
                   5、旋转设备的时候调用
                   6、子视图被移除的时候调用
                   参考请看：http://blog.logichigh.com/2011/03/16/when-does-layoutsubviews-get-called/
                   121、让UILabel在指定的地方换行
                   
                   // 换行符为\n,在需要换行的地方加上这个符号即可，如
                   label.numberOfLines = 0;
                   label.text = @"此处\n换行";
                   122、摇一摇功能
                   
                   1、打开摇一摇功能
                   [UIApplication sharedApplication].applicationSupportsShakeToEdit = YES;
                   2、让需要摇动的控制器成为第一响应者
                   [self becomeFirstResponder];
                   3、实现以下方法
                   
                   // 开始摇动
                   - (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event
                   // 取消摇动
                   - (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event
                   // 摇动结束
                   - (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event
                   123、获取图片大小
                   
                   CGFloat imageWidth = image.size.width;
                   CGFloat imageHeight = imageWidth * image.scale;
                   124、获取view的坐标在整个window上的位置
                   
                   // v上的(0, 0)点在toView上的位置
                   CGPoint point = [v convertPoint:CGPointMake(0, 0) toView:[UIApplication sharedApplication].windows.lastObject];
                   或者
                   CGPoint point = [v.superview convertPoint:v.frame.origin toView:[UIApplication sharedApplication].windows.lastObject];
                   125、提交App Store审核程序限制
                   
                   您的应用程序的未压缩大小必须小于4GB。每个Mach-O可执行文件（例如app_name.app/app_name）不能超过这些限制：
                   对于MinimumOSVersion小于7.0的应用程序：TEXT二进制文件中所有部分的总数最多为80 MB 。
                   对于MinimumOSVersion7.x到8.x的应用程序：TEXT对于二进制文件中每个体系结构片段的每个片段，最大为60 MB 。
                   对于MinimumOSVersion9.0或更高版本的应用程序：__TEXT二进制文件中所有部分的总数最多为500 MB 。参阅：iTunes Connect开发者指南
                   126、修改UISegmentedControl的字体大小
                   
                   [segment setTitleTextAttributes:@{NSFontAttributeName : [UIFont systemFontOfSize:15.0f]} forState:UIControlStateNormal];
                   127、在非ViewController的地方弹出UIAlertController对话框
                   
                   //  最好抽成一个分类
                   UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Title" message:@"message" preferredStyle:UIAlertControllerStyleAlert];
                   //...
                   id rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
                   if([rootViewController isKindOfClass:[UINavigationController class]])
{
    rootViewController = ((UINavigationController *)rootViewController).viewControllers.firstObject;
}
                   if([rootViewController isKindOfClass:[UITabBarController class]])
{
    rootViewController = ((UITabBarController *)rootViewController).selectedViewController;
}
                   [rootViewController presentViewController:alertController animated:YES completion:nil];
                   128、获取一个view所属的控制器
                   
                   // view分类方法
                   - (UIViewController *)belongViewController {
                       for (UIView *next = [self superview]; next; next = next.superview) {
                           UIResponder* nextResponder = [next nextResponder];
                           if ([nextResponder isKindOfClass:[UIViewController class]]) {
                               return (UIViewController *)nextResponder;
                           }
                       }
                       return nil;
                   }
                   129、UIImage和base64互转
                   
                   // view分类方法
                   - (NSString *)encodeToBase64String:(UIImage *)image {
                       return [UIImagePNGRepresentation(image) base64EncodedStringWithOptions:NSDataBase64Encoding64CharacterLineLength];
                   }
                   
                   - (UIImage *)decodeBase64ToImage:(NSString *)strEncodeData {
                       NSData *data = [[NSData alloc]initWithBase64EncodedString:strEncodeData options:NSDataBase64DecodingIgnoreUnknownCharacters];
                       return [UIImage imageWithData:data];
                   }
                   130、UIWebView设置背景透明
                   
                   [webView setBackgroundColor:[UIColor clearColor]];
                   [webView setOpaque:NO];
                   131、判断NSDate是不是今天
                   
                   NSDateComponents *otherDay = [[NSCalendar currentCalendar] components:NSCalendarUnitEra | NSCalendarUnitYear | NSCalendarUnitMonth | NSCalendarUnitDay fromDate:aDate];
                   NSDateComponents *today = [[NSCalendar currentCalendar] components:NSCalendarUnitEra | NSCalendarUnitYear | NSCalendarUnitMonth | NSCalendarUnitDay fromDate:[NSDate date]];
                   if([today day] == [otherDay day] &&
                      [today month] == [otherDay month] &&
                      [today year] == [otherDay year] &&
                      [today era] == [otherDay era]) {
                       // 是今天
                   }
                   132、设置tableView分割线颜色
                   
                   [self.tableView setSeparatorColor:[UIColor myColor]];
                   133、设置屏幕方向
                   
                   NSNumber *orientationTarget = [NSNumber numberWithInt:UIInterfaceOrientationLandscapeLeft];
                   [[UIDevice currentDevice] setValue:orientationTarget forKey:@"orientation"];
                   [UIViewController attemptRotationToDeviceOrientation];
                   134、比较两个颜色是否相等
                   
                   - (BOOL)isEqualToColor:(UIColor *)otherColor {
                       CGColorSpaceRef colorSpaceRGB = CGColorSpaceCreateDeviceRGB();
                       
                       UIColor *(^convertColorToRGBSpace)(UIColor*) = ^(UIColor *color) {
                           if (CGColorSpaceGetModel(CGColorGetColorSpace(color.CGColor)) == kCGColorSpaceModelMonochrome) {
                               const CGFloat *oldComponents = CGColorGetComponents(color.CGColor);
                               CGFloat components[4] = {oldComponents[0], oldComponents[0], oldComponents[0], oldComponents[1]};
                               CGColorRef colorRef = CGColorCreate( colorSpaceRGB, components );
                               
                               UIColor *color = [UIColor colorWithCGColor:colorRef];
                               CGColorRelease(colorRef);
                               return color;
                           } else
                               return color;
                       };
                       
                       UIColor *selfColor = convertColorToRGBSpace(self);
                       otherColor = convertColorToRGBSpace(otherColor);
                       CGColorSpaceRelease(colorSpaceRGB);
                       
                       return [selfColor isEqual:otherColor];
                   }
                   135、tableViewCell分割线顶到头
                   
                   - (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
                       [cell setSeparatorInset:UIEdgeInsetsZero];
                       [cell setLayoutMargins:UIEdgeInsetsZero];
                       cell.preservesSuperviewLayoutMargins = NO;
                   }
                   
                   - (void)viewDidLayoutSubviews {
                       [self.tableView setSeparatorInset:UIEdgeInsetsZero];
                       [self.tableView setLayoutMargins:UIEdgeInsetsZero];
                   }
                   136、不让控制器的view随着控制器的xib拉伸或压缩
                   
                   self.view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
                   137、cocoaPods报错 : [!] Unable to add a source with url https://github.com/CocoaPods/Specs.git named master-1.
                   
                   You can try adding it manually in ~/.cocoapods/repos or via pod repo add.
                   
                   解决方法：这是因为电脑里安装了另外一个Xcode导致cocoapods找不到路径了
                   在终端执行 sudo xcode-select -switch /Applications/Xcode.app 即可
                   138、安装cocoapods的时候出现 ERROR: While executing gem ... (Errno::EPERM)
                   
                   Operation not permitted - /usr/bin/pod
                   解决办法：直接在终端执行 sudo gem install -n /usr/local/bin cocoapods
                   139、在状态栏增加网络请求的菊花，类似safari加载网页的时候状态栏菊花
                   
                   [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
                   140、检查一个rect是否包含一个point
                   
                   // point是否在rect内
                   BOOL isContains = CGRectContainsPoint(rect, point);
                   141、在指定的宽度下，让UILabel自动设置最佳font
                   
                   label.adjustsFontSizeToFitWidth = YES;
                   142、将一个image保存在相册中
                   
                   UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil);
                   
                   或者
#import <Photos/Photos.h>
                   [[PHPhotoLibrary sharedPhotoLibrary] performChanges:^{
    PHAssetChangeRequest *changeRequest = [PHAssetChangeRequest creationRequestForAssetFromImage:image];
    changeRequest.creationDate          = [NSDate date];
} completionHandler:^(BOOL success, NSError *error) {
    if (success) {
        NSLog(@"successfully saved");
    }
    else {
        NSLog(@"error saving to photos: %@", error);
    }
}];
                   143、修改cell.imageView的大小
                   
                   UIImage *icon = [UIImage imageNamed:@""];
                   CGSize itemSize = CGSizeMake(30, 30);
                   UIGraphicsBeginImageContextWithOptions(itemSize, NO ,0.0);
                   CGRect imageRect = CGRectMake(0.0, 0.0, itemSize.width, itemSize.height);
                   [icon drawInRect:imageRect];
                   cell.imageView.image = UIGraphicsGetImageFromCurrentImageContext();
                   UIGraphicsEndImageContext();
                   144、为一个view添加虚线边框
                   
                   CAShapeLayer *border = [CAShapeLayer layer];
                   border.strokeColor = [UIColor colorWithRed:67/255.0f green:37/255.0f blue:83/255.0f alpha:1].CGColor;
                   border.fillColor = nil;
                   border.lineDashPattern = @[@4, @2];
                   border.path = [UIBezierPath bezierPathWithRect:view.bounds].CGPath;
                   border.frame = view.bounds;
                   [view.layer addSublayer:border];
                   145、UITextView中打开或禁用复制，剪切，选择，全选等功能
                   
                   // 继承UITextView重写这个方法
                   - (BOOL)canPerformAction:(SEL)action withSender:(id)sender
{
    // 返回NO为禁用，YES为开启
    // 粘贴
    if (action == @selector(paste:)) return NO;
    // 剪切
    if (action == @selector(cut:)) return NO;
    // 复制
    if (action == @selector(copy:)) return NO;
    // 选择
    if (action == @selector(select:)) return NO;
    // 选中全部
    if (action == @selector(selectAll:)) return NO;
    // 删除
    if (action == @selector(delete:)) return NO;
    // 分享
    if (action == @selector(share)) return NO;
    return [super canPerformAction:action withSender:sender];
}
                       
                       2、当使用-performSelector:withObject:withObject:afterDelay:方法时，需要传入多参数问题
                       
                       // 方法一、
                       // 把参数放进一个数组／字典，直接把数组／字典当成一个参数传过去，具体方法实现的地方再解析这个数组／字典
                       NSArray * array =
                       [NSArray arrayWithObjects: @"first", @"second", nil];
                       [self performSelector:@selector(fooFirstInput:) withObject: array afterDelay:15.0];
                       
                       // 方法二、
                       // 使用NSInvocation
                       SEL aSelector = NSSelectorFromString(@"doSoming:argument2:");
                       NSInteger argument1 = 10;
                       NSString *argument2 = @"argument2";
                       if([self respondsToSelector:aSelector]) {
                           NSInvocation *inv = [NSInvocation invocationWithMethodSignature:[self methodSignatureForSelector:aSelector]];
                           [inv setSelector:aSelector];
                           [inv setTarget:self];
                           [inv setArgument:&(argument1) atIndex:2];
                           [inv setArgument:&(argument2) atIndex:3];
                           [inv performSelector:@selector(invoke) withObject:nil afterDelay:15.0];
                       }
                       3、UILabel显示不同颜色字体
                       
                       NSMutableAttributedString * string = [[NSMutableAttributedString alloc] initWithString:label.text];
                       [string addAttribute:NSForegroundColorAttributeName value:[UIColor redColor] range:NSMakeRange(0,5)];
                       [string addAttribute:NSForegroundColorAttributeName value:[UIColor greenColor] range:NSMakeRange(5,6)];
                       [string addAttribute:NSForegroundColorAttributeName value:[UIColor blueColor] range:NSMakeRange(11,5)];
                       label.attributedText = string;
                       4、比较两个CGRect/CGSize/CGPoint是否相等
                       
                       if (CGRectEqualToRect(rect1, rect2)) { // 两个区域相等
                           // do some
                       }
                       if (CGPointEqualToPoint(point1, point2)) { // 两个点相等
                           // do some
                       }
                       if (CGSizeEqualToSize(size1, size2)) { // 两个size相等
                           // do some
                       }
                       5、比较两个NSDate相差多少小时
                       
                       NSDate* date1 = someDate;
                       NSDate* date2 = someOtherDate;
                       NSTimeInterval distanceBetweenDates = [date1 timeIntervalSinceDate:date2];
                       double secondsInAnHour = 3600;
                       // 除以3600是把秒化成小时，除以60得到结果为相差的分钟数
                       NSInteger hoursBetweenDates = distanceBetweenDates / secondsInAnHour;
                       6、每个cell之间增加间距
                       
                       // 方法一，每个分区只显示一行cell，分区头当作你想要的间距(注意，从数据源数组中取值的时候需要用indexPath.section而不是indexPath.row)
                       - (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
                       {
                           return yourArry.count;
                       }
                       - (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
                       {
                           return 1;
                       }
                       -(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
                       {
                           return cellSpacingHeight;
                       }
                       
                       // 方法二，在cell的contentView上加个稍微低一点的view，cell上原本的内容放在你的view上，而不是contentView上，这样能伪造出一个间距来。
                       
                       // 方法三，自定义cell，重写setFrame：方法
                       - (void)setFrame:(CGRect)frame
                       {
                           frame.size.height -= 20;
                           [super setFrame:frame];
                       }
                       7、播放一张张连续的图片
                       
                       // 加入现在有三张图片分别为animate_1、animate_2、animate_3
                       // 方法一
                       imageView.animationImages = @[[UIImage imageNamed:@"animate_1"], [UIImage imageNamed:@"animate_2"], [UIImage imageNamed:@"animate_3"]];
                       imageView.animationDuration = 1.0;
                       // 方法二
                       imageView.image = [UIImage animatedImageNamed:@"animate_" duration:1.0];
                       // 方法二解释下，这个方法会加载animate_为前缀的，后边0-1024，也就是animate_0、animate_1一直到animate_1024
                       8、加载gif图片
                       
                       推荐使用这个框架 FLAnimatedImage
                       9、防止离屏渲染为image添加圆角
                       
                       // image分类
                       - (UIImage *)circleImage
                       {
                           // NO代表透明
                           UIGraphicsBeginImageContextWithOptions(self.size, NO, 1);
                           // 获得上下文
                           CGContextRef ctx = UIGraphicsGetCurrentContext();
                           // 添加一个圆
                           CGRect rect = CGRectMake(0, 0, self.size.width, self.size.height);
                           // 方形变圆形
                           CGContextAddEllipseInRect(ctx, rect);
                           // 裁剪
                           CGContextClip(ctx);
                           // 将图片画上去
                           [self drawInRect:rect];
                           UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
                           UIGraphicsEndImageContext();
                           return image;
                       }
                       10、查看系统所有字体
                       
                       // 打印字体
                       for (id familyName in [UIFont familyNames]) {
                           NSLog(@"%@", familyName);
                           for (id fontName in [UIFont fontNamesForFamilyName:familyName]) NSLog(@"  %@", fontName);
                       }
                       // 也可以进入这个网址查看 http://iosfonts.com/
                       11、获取随机数
                       
                       NSInteger i = arc4random();
                       12、获取随机数小数(0-1之间)
                       
#define ARC4RANDOM_MAX      0x100000000
                       double val = ((double)arc4random() / ARC4RANDOM_MAX);
                       13、AVPlayer视频播放完成的通知监听
                       
                       [[NSNotificationCenter defaultCenter]
                        addObserver:self
                        selector:@selector(videoPlayEnd)
                        name:AVPlayerItemDidPlayToEndTimeNotification
                        object:nil];
                       14、判断两个rect是否有交叉
                       
                       if (CGRectIntersectsRect(rect1, rect2)) {
                       }
                       15、判断一个字符串是否为数字
                       
                       NSCharacterSet *notDigits = [[NSCharacterSet decimalDigitCharacterSet] invertedSet];
                       if ([str rangeOfCharacterFromSet:notDigits].location == NSNotFound)
                       {
                           // 是数字
                       } else
                       {
                           // 不是数字
                       }
                       16、将一个view保存为pdf格式
                       
                       - (void)createPDFfromUIView:(UIView*)aView saveToDocumentsWithFileName:(NSString*)aFilename
                       {
                           NSMutableData *pdfData = [NSMutableData data];
                           UIGraphicsBeginPDFContextToData(pdfData, aView.bounds, nil);
                           UIGraphicsBeginPDFPage();
                           CGContextRef pdfContext = UIGraphicsGetCurrentContext();
                           [aView.layer renderInContext:pdfContext];
                           UIGraphicsEndPDFContext();
                           
                           NSArray* documentDirectories = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
                           NSString* documentDirectory = [documentDirectories objectAtIndex:0];
                           NSString* documentDirectoryFilename = [documentDirectory stringByAppendingPathComponent:aFilename];
                           [pdfData writeToFile:documentDirectoryFilename atomically:YES];
                           NSLog(@"documentDirectoryFileName: %@",documentDirectoryFilename);
                       }
                       17、让一个view在父视图中心
                       
                       child.center = [parent convertPoint:parent.center fromView:parent.superview];
                       18、获取当前导航控制器下前一个控制器
                       
                       - (UIViewController *)backViewController
                       {
                           NSInteger myIndex = [self.navigationController.viewControllers indexOfObject:self];
                           
                           if ( myIndex != 0 && myIndex != NSNotFound ) {
                               return [self.navigationController.viewControllers objectAtIndex:myIndex-1];
                           } else {
                               return nil;
                           }
                       }
                       19、保存UIImage到本地
                       
                       NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
                       NSString *filePath = [[paths objectAtIndex:0] stringByAppendingPathComponent:@"Image.png"];
                       
                       [UIImagePNGRepresentation(image) writeToFile:filePath atomically:YES];
                       20、键盘上方增加工具栏
                       
                       UIToolbar *keyboardDoneButtonView = [[UIToolbar alloc] init];
                       [keyboardDoneButtonView sizeToFit];
                       UIBarButtonItem *doneButton = [[UIBarButtonItem alloc] initWithTitle:@"Done"
                                                                                      style:UIBarButtonItemStyleBordered target:self
                                                                                     action:@selector(doneClicked:)];
                       [keyboardDoneButtonView setItems:[NSArray arrayWithObjects:doneButton, nil]];
                       txtField.inputAccessoryView = keyboardDoneButtonView;
                       21、copy一个view
                       
                       因为UIView没有实现copy协议，因此找不到copyWithZone方法，使用copy的时候导致崩溃
                       但是我们可以通过归档再解档实现copy，这相当于对视图进行了一次深拷贝，代码如下
                       id copyOfView =
                       [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject:originalView]];
                       22、在image上绘制文字并生成新的image
                       
                       UIFont *font = [UIFont boldSystemFontOfSize:12];
                       UIGraphicsBeginImageContext(image.size);
                       [image drawInRect:CGRectMake(0,0,image.size.width,image.size.height)];
                       CGRect rect = CGRectMake(point.x, point.y, image.size.width, image.size.height);
                       [[UIColor whiteColor] set];
                       [text drawInRect:CGRectIntegral(rect) withFont:font];
                       UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
                       UIGraphicsEndImageContext();
                       23、判断一个view是否为另一个view的子视图
                       
                       // 如果myView是self.view本身，也会返回yes
                       BOOL isSubView = [myView isDescendantOfView:self.view];
                       24、判断一个字符串是否包含另一个字符串
                       
                       // 方法一、这种方法只适用于iOS8之后，如果是配iOS8之前用方法二
                       if ([str containsString:otherStr]) NSLog(@"包含");
                       
                       // 方法二
                       NSRange range = [str rangeOfString:otherStr];
                       if (range.location != NSNotFound) NSLog(@"包含");
                       25、UICollectionView自动滚动到某行
                       
                       // 重写viewDidLayoutSubviews方法
                       -(void)viewDidLayoutSubviews {
                           [super viewDidLayoutSubviews];
                           [self.collectionView scrollToItemAtIndexPath:indexPath atScrollPosition:UICollectionViewScrollPositionCenteredVertically animated:NO];
                       }
                       26、修改系统UIAlertController
                       
                       // 但是据说这种方法会被App Store拒绝(慎用！)
                       UIAlertController *alertVC = [UIAlertController alertControllerWithTitle:@"" message:@"" preferredStyle:UIAlertControllerStyleActionSheet];
                       NSMutableAttributedString *hogan = [[NSMutableAttributedString alloc] initWithString:@"我是一个大文本"];
                       [hogan addAttribute:NSFontAttributeName
                                     value:[UIFont systemFontOfSize:30]
                                     range:NSMakeRange(4, 1)];
                       [hogan addAttribute:NSForegroundColorAttributeName
                                     value:[UIColor redColor]
                                     range:NSMakeRange(4, 1)];
                       [alertVC setValue:hogan forKey:@"attributedTitle"];
                       
                       UIAlertAction *button = [UIAlertAction actionWithTitle:@"Label text" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action){ }];
                       UIImage *accessoryImage = [UIImage imageNamed:@"1"];
                       [button setValue:accessoryImage forKey:@"image"];
                       [alertVC addAction:button];
                       [self presentViewController:alertVC animated:YES completion:nil];
                       27、判断某一行的cell是否已经显示
                       
                       CGRect cellRect = [tableView rectForRowAtIndexPath:indexPath];
                       BOOL completelyVisible = CGRectContainsRect(tableView.bounds, cellRect);
                       28、让导航控制器pop回指定的控制器
                       
                       NSMutableArray *allViewControllers = [NSMutableArray arrayWithArray:[self.navigationController viewControllers]];
                       for (UIViewController *aViewController in allViewControllers) {
                           if ([aViewController isKindOfClass:[RequiredViewController class]]) {
                               [self.navigationController popToViewController:aViewController animated:NO];
                           }
                       }
                       29、动画修改label上的文字
                       
                       // 方法一
                       CATransition *animation = [CATransition animation];
                       animation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
                       animation.type = kCATransitionFade;
                       animation.duration = 0.75;
                       [self.label.layer addAnimation:animation forKey:@"kCATransitionFade"];
                       self.label.text = @"New";
                       
                       // 方法二
                       [UIView transitionWithView:self.label
                                         duration:0.25f
                                          options:UIViewAnimationOptionTransitionCrossDissolve
                                       animations:^{
                                           
                                           self.label.text = @"Well done!";
                                           
                                       } completion:nil];
                       
                       // 方法三
                       [UIView animateWithDuration:1.0
                                        animations:^{
                                            self.label.alpha = 0.0f;
                                            self.label.text = @"newText";
                                            self.label.alpha = 1.0f;
                                        }];
                       30、判断字典中是否包含某个key值
                       
                       if ([dic objectForKey:@"yourKey"]) {
                           NSLog(@"有这个值");
                       } else {
                           NSLog(@"没有这个值");
                       }
                       31、获取屏幕方向
                       
                       UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;
                       
                       if(orientation == 0) //Default orientation
                       //默认
                       else if(orientation == UIInterfaceOrientationPortrait)
                       //竖屏
                       else if(orientation == UIInterfaceOrientationLandscapeLeft)
                       // 左横屏
                       else if(orientation == UIInterfaceOrientationLandscapeRight)
                       //右横屏
                       32、设置UIImage的透明度
                       
                       // 方法一、添加UIImage分类
                       - (UIImage *)imageByApplyingAlpha:(CGFloat) alpha {
                           UIGraphicsBeginImageContextWithOptions(self.size, NO, 0.0f);
                           
                           CGContextRef ctx = UIGraphicsGetCurrentContext();
                           CGRect area = CGRectMake(0, 0, self.size.width, self.size.height);
                           
                           CGContextScaleCTM(ctx, 1, -1);
                           CGContextTranslateCTM(ctx, 0, -area.size.height);
                           
                           CGContextSetBlendMode(ctx, kCGBlendModeMultiply);
                           
                           CGContextSetAlpha(ctx, alpha);
                           
                           CGContextDrawImage(ctx, area, self.CGImage);
                           
                           UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
                           
                           UIGraphicsEndImageContext();
                           
                           return newImage;
                       }
                       
                       // 方法二、如果没有奇葩需求，干脆用UIImageView设置透明度
                       UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageWithName:@"yourImage"]];
                       imageView.alpha = 0.5;
                       33、Attempt to mutate immutable object with insertString:atIndex:
                       
                       这个错是因为你拿字符串调用insertString:atIndex:方法的时候，调用对象不是NSMutableString，应该先转成这个类型再调用
                       34、UIWebView添加单击手势不响应
                       
                       UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(webViewClick)];
                       tap.delegate = self;
                       [_webView addGestureRecognizer:tap];
                       
                       // 因为webView本身有一个单击手势，所以再添加会造成手势冲突，从而不响应。需要绑定手势代理，并实现下边的代理方法
                       - (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer{
                           return YES;
                       }
                       35、获取手机RAM容量
                       
                       // 需要导入#import <mach/mach.h>
                       mach_port_t host_port;
                       mach_msg_type_number_t host_size;
                       vm_size_t pagesize;
                       
                       host_port = mach_host_self();
                       host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
                       host_page_size(host_port, &pagesize);
                       
                       vm_statistics_data_t vm_stat;
                       
                       if (host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size) != KERN_SUCCESS) {
                           NSLog(@"Failed to fetch vm statistics");
                       }
                       
                       /* Stats in bytes */
                       natural_t mem_used = (vm_stat.active_count +
                                             vm_stat.inactive_count +
                                             vm_stat.wire_count) * pagesize;
                       natural_t mem_free = vm_stat.free_count * pagesize;
                       natural_t mem_total = mem_used + mem_free;
                       NSLog(@"已用: %u 可用: %u 总共: %u", mem_used, mem_free, mem_total);
                       36、地图上两个点之间的实际距离
                       
                       // 需要导入#import <CoreLocation/CoreLocation.h>
                       CLLocation *locA = [[CLLocation alloc] initWithLatitude:34 longitude:113];
                       CLLocation *locB = [[CLLocation alloc] initWithLatitude:31.05 longitude:121.76];
                       // CLLocationDistance求出的单位为米
                       CLLocationDistance distance = [locA distanceFromLocation:locB];
                       37、在应用中打开设置的某个界面
                       
                       // 打开设置->通用
                       [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"prefs:root=General"]];
                       
                       // 以下是设置其他界面
                   prefs:root=General&path=About
                   prefs:root=General&path=ACCESSIBILITY
                   prefs:root=AIRPLANE_MODE
                   prefs:root=General&path=AUTOLOCK
                   prefs:root=General&path=USAGE/CELLULAR_USAGE
                   prefs:root=Brightness
                   prefs:root=Bluetooth
                   prefs:root=General&path=DATE_AND_TIME
                   prefs:root=FACETIME
                   prefs:root=General
                   prefs:root=General&path=Keyboard
                   prefs:root=CASTLE
                   prefs:root=CASTLE&path=STORAGE_AND_BACKUP
                   prefs:root=General&path=INTERNATIONAL
                   prefs:root=LOCATION_SERVICES
                   prefs:root=ACCOUNT_SETTINGS
                   prefs:root=MUSIC
                   prefs:root=MUSIC&path=EQ
                   prefs:root=MUSIC&path=VolumeLimit
                   prefs:root=General&path=Network
                   prefs:root=NIKE_PLUS_IPOD
                   prefs:root=NOTES
                   prefs:root=NOTIFICATIONS_ID
                   prefs:root=Phone
                   prefs:root=Photos
                   prefs:root=General&path=ManagedConfigurationList
                   prefs:root=General&path=Reset
                   prefs:root=Sounds&path=Ringtone
                   prefs:root=Safari
                   prefs:root=General&path=Assistant
                   prefs:root=Sounds
                   prefs:root=General&path=SOFTWARE_UPDATE_LINK
                   prefs:root=STORE
                   prefs:root=TWITTER
                   prefs:root=FACEBOOK
                   prefs:root=General&path=USAGE prefs:root=VIDEO
                   prefs:root=General&path=Network/VPN
                   prefs:root=Wallpaper
                   prefs:root=WIFI
                   prefs:root=INTERNET_TETHERING
                   prefs:root=Phone&path=Blocked
                   prefs:root=DO_NOT_DISTURB
                       38、在UITextView中显示html文本
                       
                       UITextView *textView = [[UITextView alloc] initWithFrame:CGRectMake(20, 30, 100, 199)];
                       textView.backgroundColor = [UIColor redColor];
                       [self.view addSubview:textView];
                       NSString *htmlString = @"<h1>Header</h1><h2>Subheader</h2><p>Some <em>text</em></p>![](http://blogs.babble.com/famecrawler/files/2010/11/mickey_mouse-1097.jpg)";
                       NSAttributedString *attributedString = [[NSAttributedString alloc] initWithData: [htmlString dataUsingEncoding:NSUnicodeStringEncoding] options: @{ NSDocumentTypeDocumentAttribute: NSHTMLTextDocumentType } documentAttributes: nil error: nil];
                       textView.attributedText = attributedString;
                       39、监听scrollView是否滚动到了顶部／底部
                       
                       -(void)scrollViewDidScroll: (UIScrollView*)scrollView
                       {
                           float scrollViewHeight = scrollView.frame.size.height;
                           float scrollContentSizeHeight = scrollView.contentSize.height;
                           float scrollOffset = scrollView.contentOffset.y;
                           
                           if (scrollOffset == 0)
                           {
                               // 滚动到了顶部
                           }
                           else if (scrollOffset + scrollViewHeight == scrollContentSizeHeight)
                           {
                               // 滚动到了底部
                           }
                       }
                       40、UISlider增量／减量为固定值(假如为5)
                       
                       - (void)setupSlider
                       {
                           UISlider *slider = [[UISlider alloc] init];
                           [self.view addSubview:slider];
                           [slider addTarget:self action:@selector(sliderAction:) forControlEvents:UIControlEventValueChanged];
                           slider.maximumValue = 100;
                           slider.minimumValue = 0;
                           slider.frame = CGRectMake(200, 20, 100, 30);
                       }
                       
                       - (void)sliderAction:(UISlider *)slider
                       {
                           [slider setValue:((int)((slider.value + 2.5) / 5) * 5) animated:NO];
                       }
                       41、选中textField或者textView所有文本(我这里以textView为例)
                       
                       [self.textView setSelectedTextRange:[self.textView textRangeFromPosition:self.textView.beginningOfDocument toPosition:self.textView.endOfDocument]]
                       42、从导航控制器中删除某个控制器
                       
                       // 方法一、知道这个控制器所处的导航控制器下标
                       NSMutableArray *navigationArray = [[NSMutableArray alloc] initWithArray: self.navigationController.viewControllers];
                       [navigationArray removeObjectAtIndex: 2];
                       self.navigationController.viewControllers = navigationArray;
                       
                       // 方法二、知道具体是哪个控制器
                       NSArray* tempVCA = [self.navigationController viewControllers];
                       
                       for(UIViewController *tempVC in tempVCA)
                       {
                           if([tempVC isKindOfClass:[urViewControllerClass class]])
                           {
                               [tempVC removeFromParentViewController];
                           }
                       }
                       43、隐藏UITextView/UITextField光标
                       
                       textField.tintColor = [UIColor clearColor];
                       44、当UITextView/UITextField中没有文字时，禁用回车键
                       
                       textField.enablesReturnKeyAutomatically = YES;
                       45、字符串encode编码(编码url字符串不成功的问题)
                       
                       // 我们一般用这个方法处理stringByAddingPercentEscapesUsingEncoding但是这个方法好想不会处理／和&这种特殊符号，这种情况就需要用下边这个方法处理
                       @implementation NSString (NSString_Extended)
                       - (NSString *)urlencode {
                           NSMutableString *output = [NSMutableString string];
                           const unsigned char *source = (const unsigned char *)[self UTF8String];
                           int sourceLen = strlen((const char *)source);
                           for (int i = 0; i < sourceLen; ++i) {
                               const unsigned char thisChar = source[i];
                               if (thisChar == ' '){
                                   [output appendString:@"+"];
                               } else if (thisChar == '.' || thisChar == '-' || thisChar == '_' || thisChar == '~' ||
                                          (thisChar >= 'a' && thisChar <= 'z') ||
                                          (thisChar >= 'A' && thisChar <= 'Z') ||
                                          (thisChar >= '0' && thisChar <= '9')) {
                                   [output appendFormat:@"%c", thisChar];
                               } else {
                                   [output appendFormat:@"%%%02X", thisChar];
                               }
                           }
                           return output;
                       }
                       46、计算UILabel上某段文字的frame
                       
                       @implementation UILabel (TextRect)
                       
                       - (CGRect)boundingRectForCharacterRange:(NSRange)range
                       {
                           NSTextStorage *textStorage = [[NSTextStorage alloc] initWithAttributedString:[self attributedText]];
                           NSLayoutManager *layoutManager = [[NSLayoutManager alloc] init];
                           [textStorage addLayoutManager:layoutManager];
                           NSTextContainer *textContainer = [[NSTextContainer alloc] initWithSize:[self bounds].size];
                           textContainer.lineFragmentPadding = 0;
                           [layoutManager addTextContainer:textContainer];
                           NSRange glyphRange;
                           [layoutManager characterRangeForGlyphRange:range actualGlyphRange:&glyphRange];
                           return [layoutManager boundingRectForGlyphRange:glyphRange inTextContainer:textContainer];
                       }
                       47、获取随机UUID
                       
                       NSString *result;
                       if([[[UIDevice currentDevice] systemVersion] floatValue] > 6.0)
                       {
                           result = [[NSUUID UUID] UUIDString];
                       }
                       else
                       {
                           CFUUIDRef uuidRef = CFUUIDCreate(NULL);
                           CFStringRef uuid = CFUUIDCreateString(NULL, uuidRef);
                           CFRelease(uuidRef);
                           result = (__bridge_transfer NSString *)uuid;
                       }
                       48、仿苹果抖动动画
                       
#define RADIANS(degrees) (((degrees) * M_PI) / 180.0)
                       
                       - (void)startAnimate {
                           view.transform = CGAffineTransformRotate(CGAffineTransformIdentity, RADIANS(-5));
                           
                           [UIView animateWithDuration:0.25 delay:0.0 options:(UIViewAnimationOptionAllowUserInteraction | UIViewAnimationOptionRepeat | UIViewAnimationOptionAutoreverse) animations:^ {
                               view.transform = CGAffineTransformRotate(CGAffineTransformIdentity, RADIANS(5));
                           } completion:nil];
                       }
                       
                       - (void)stopAnimate {
                           [UIView animateWithDuration:0.25 delay:0.0 options:(UIViewAnimationOptionAllowUserInteraction | UIViewAnimationOptionBeginFromCurrentState | UIViewAnimationOptionCurveLinear) animations:^ {
                               view.transform = CGAffineTransformIdentity;
                           } completion:nil];
                       }
                       49、修改UISearBar内部背景颜色
                       
                       UITextField *textField = [_searchBar valueForKey:@"_searchField"];
                       textField.backgroundColor = [UIColor redColor];
                       50、UITextView滚动到顶部
                       
                       // 方法一
                       [self.textView scrollRangeToVisible:NSMakeRange(0, 0)];
                       // 方法二
                       [self.textView setContentOffset:CGPointZero animated:YES];
                       51、通知监听APP生命周期
                       
                       UIApplicationDidEnterBackgroundNotification 应用程序进入后台
                       UIApplicationWillEnterForegroundNotification 应用程序将要进入前台
                       UIApplicationDidFinishLaunchingNotification 应用程序完成启动
                       UIApplicationDidFinishLaunchingNotification 应用程序由挂起变的活跃
                       UIApplicationWillResignActiveNotification 应用程序挂起(有电话进来或者锁屏)
                       UIApplicationDidReceiveMemoryWarningNotification 应用程序收到内存警告
                       UIApplicationDidReceiveMemoryWarningNotification 应用程序终止(后台杀死、手机关机等)
                       UIApplicationSignificantTimeChangeNotification 当有重大时间改变(凌晨0点，设备时间被修改，时区改变等)
                       UIApplicationWillChangeStatusBarOrientationNotification 设备方向将要改变
                       UIApplicationDidChangeStatusBarOrientationNotification 设备方向改变
                       UIApplicationWillChangeStatusBarFrameNotification 设备状态栏frame将要改变
                       UIApplicationDidChangeStatusBarFrameNotification 设备状态栏frame改变
                       UIApplicationBackgroundRefreshStatusDidChangeNotification 应用程序在后台下载内容的状态发生变化
                       UIApplicationProtectedDataWillBecomeUnavailable 本地受保护的文件被锁定,无法访问
                       UIApplicationProtectedDataWillBecomeUnavailable 本地受保护的文件可用了
                       52、触摸事件类型
                       
                       UIControlEventTouchCancel 取消控件当前触发的事件
                       UIControlEventTouchDown 点按下去的事件
                       UIControlEventTouchDownRepeat 重复的触动事件
                       UIControlEventTouchDragEnter 手指被拖动到控件的边界的事件
                       UIControlEventTouchDragExit 一个手指从控件内拖到外界的事件
                       UIControlEventTouchDragInside 手指在控件的边界内拖动的事件
                       UIControlEventTouchDragOutside 手指在控件边界之外被拖动的事件
                       UIControlEventTouchUpInside 手指处于控制范围内的触摸事件
                       UIControlEventTouchUpOutside 手指超出控制范围的控制中的触摸事件
                       53、UITextField文字周围增加边距
                       
                       // 子类化UITextField，增加insert属性
                       @interface WZBTextField : UITextField
                       @property (nonatomic, assign) UIEdgeInsets insets;
                       @end
                       
                       // 在.m文件重写下列方法
                       - (CGRect)textRectForBounds:(CGRect)bounds {
                           CGRect paddedRect = UIEdgeInsetsInsetRect(bounds, self.insets);
                           if (self.rightViewMode == UITextFieldViewModeAlways || self.rightViewMode == UITextFieldViewModeUnlessEditing) {
                               return [self adjustRectWithWidthRightView:paddedRect];
                           }
                           return paddedRect;
                       }
                       
                       - (CGRect)placeholderRectForBounds:(CGRect)bounds {
                           CGRect paddedRect = UIEdgeInsetsInsetRect(bounds, self.insets);
                           
                           if (self.rightViewMode == UITextFieldViewModeAlways || self.rightViewMode == UITextFieldViewModeUnlessEditing) {
                               return [self adjustRectWithWidthRightView:paddedRect];
                           }
                           return paddedRect;
                       }
                       
                       - (CGRect)editingRectForBounds:(CGRect)bounds {
                           CGRect paddedRect = UIEdgeInsetsInsetRect(bounds, self.insets);
                           if (self.rightViewMode == UITextFieldViewModeAlways || self.rightViewMode == UITextFieldViewModeWhileEditing) {
                               return [self adjustRectWithWidthRightView:paddedRect];
                           }
                           return paddedRect;
                       }
                       
                       - (CGRect)adjustRectWithWidthRightView:(CGRect)bounds {
                           CGRect paddedRect = bounds;
                           paddedRect.size.width -= CGRectGetWidth(self.rightView.frame);
                           
                           return paddedRect;
                       }
                       54、监听UISlider拖动状态
                       
                       // 添加事件
                       [slider addTarget:self action:@selector(sliderValurChanged:forEvent:) forControlEvents:UIControlEventValueChanged];
                       
                       // 实现方法
                       - (void)sliderValurChanged:(UISlider*)slider forEvent:(UIEvent*)event {
                           UITouch *touchEvent = [[event allTouches] anyObject];
                           switch (touchEvent.phase) {
                               case UITouchPhaseBegan:
                                   NSLog(@"开始拖动");
                                   break;
                               case UITouchPhaseMoved:
                                   NSLog(@"正在拖动");
                                   break;
                               case UITouchPhaseEnded:
                                   NSLog(@"结束拖动");
                                   break;
                               default:
                                   break;
                           }
                       }
                       55、设置UITextField光标位置
                       
                       // textField需要设置的textField，index要设置的光标位置
                       - (void)cursorLocation:(UITextField *)textField index:(NSInteger)index
                       {
                           NSRange range = NSMakeRange(index, 0);
                           UITextPosition *start = [textField positionFromPosition:[textField beginningOfDocument] offset:range.location];
                           UITextPosition *end = [textField positionFromPosition:start offset:range.length];
                           [textField setSelectedTextRange:[textField textRangeFromPosition:start toPosition:end]];
                       }
                       56、去除webView底部黑色
                       
                       [webView setBackgroundColor:[UIColor clearColor]];
                       [webView setOpaque:NO];
                       
                       for (UIView *v1 in [webView subviews])
                       {
                           if ([v1 isKindOfClass:[UIScrollView class]])
                           {
                               for (UIView *v2 in v1.subviews)
                               {
                                   if ([v2 isKindOfClass:[UIImageView class]])
                                   {
                                       v2.hidden = YES;
                                   }
                               }
                           }
                       }
                       57、获取collectionViewCell在屏幕中的frame
                       
                       UICollectionViewLayoutAttributes *attributes = [collectionView layoutAttributesForItemAtIndexPath:indexPath];
                       CGRect cellRect = attributes.frame;
                       CGRect cellFrameInSuperview = [collectionView convertRect:cellRect toView:[cv superview]];
                       58、比较两个UIImage是否相等
                       
                       - (BOOL)image:(UIImage *)image1 isEqualTo:(UIImage *)image2
                       {
                           NSData *data1 = UIImagePNGRepresentation(image1);
                           NSData *data2 = UIImagePNGRepresentation(image2);
                           
                           return [data1 isEqual:data2];
                       }
                       59、解决当UIScrollView上有UIButton的时候，触摸到button滑动不了的问题
                       
                       // 子类化UIScrollView，并重写以下方法
                       - (instancetype)initWithFrame:(CGRect)frame {
                           if (self = [super initWithFrame:frame]) {
                               self.delaysContentTouches = NO;
                           }
                           
                           return self;
                       }
                       
                       - (BOOL)touchesShouldCancelInContentView:(UIView *)view {
                           if ([view isKindOfClass:UIButton.class]) {
                               return YES;
                           }
                           
                           return [super touchesShouldCancelInContentView:view];
                       }
                       60、UITextView中的文字添加阴影效果
                       
                       - (void)setTextLayer:(UITextView *)textView color:(UIColor *)color
                       {
                           CALayer *textLayer = ((CALayer *)[textView.layer.sublayers objectAtIndex:0]);
                           textLayer.shadowColor = color.CGColor;
                           textLayer.shadowOffset = CGSizeMake(0.0f, 1.0f);
                           textLayer.shadowOpacity = 1.0f;
                           textLayer.shadowRadius = 1.0f;
                       }
                       61、MD5加密
                       
                       + (NSString *)md5:(NSString *)str
                       {
                           const char *concat_str = [str UTF8String];
                           unsigned char result[CC_MD5_DIGEST_LENGTH];
                           CC_MD5(concat_str, (unsigned int)strlen(concat_str), result);
                           NSMutableString *hash = [NSMutableString string];
                           for (int i =0; i <16; i++){
                               [hash appendFormat:@"%02X", result[i]];
                           }
                           return [hash uppercaseString];
                       }
                       62、base64加密
                       
                       @interface NSData (Base64)
                       /**
                        *  @brief  字符串base64后转data
                        */
                       + (NSData *)dataWithBase64EncodedString:(NSString *)string
                       {
                           if (![string length]) return nil;
                           NSData *decoded = nil;
#if __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_10_9 || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_7_0
                           if (![NSData instancesRespondToSelector:@selector(initWithBase64EncodedString:options:)])
                           {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
                               decoded = [[self alloc] initWithBase64Encoding:[string stringByReplacingOccurrencesOfString:@"[^A-Za-z0-9+/=]" withString:@"" options:NSRegularExpressionSearch range:NSMakeRange(0, [string length])]];
#pragma clang diagnostic pop
                           }
                           else
#endif
                           {
                               decoded = [[self alloc] initWithBase64EncodedString:string options:NSDataBase64DecodingIgnoreUnknownCharacters];
                           }
                           return [decoded length]? decoded: nil;
                       }
                       /**
                        *  @brief  NSData转string
                        *  @param wrapWidth 换行长度  76  64
                        */
                       - (NSString *)base64EncodedStringWithWrapWidth:(NSUInteger)wrapWidth
                       {
                           if (![self length]) return nil;
                           NSString *encoded = nil;
#if __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_10_9 || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_7_0
                           if (![NSData instancesRespondToSelector:@selector(base64EncodedStringWithOptions:)])
                           {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
                               encoded = [self base64Encoding];
#pragma clang diagnostic pop
                               
                           }
                           else
#endif
                           {
                               switch (wrapWidth)
                               {
                                   case 64:
                                   {
                                       return [self base64EncodedStringWithOptions:NSDataBase64Encoding64CharacterLineLength];
                                   }
                                   case 76:
                                   {
                                       return [self base64EncodedStringWithOptions:NSDataBase64Encoding76CharacterLineLength];
                                   }
                                   default:
                                   {
                                       encoded = [self base64EncodedStringWithOptions:(NSDataBase64EncodingOptions)0];
                                   }
                               }
                           }
                           if (!wrapWidth || wrapWidth >= [encoded length])
                           {
                               return encoded;
                           }
                           wrapWidth = (wrapWidth / 4) * 4;
                           NSMutableString *result = [NSMutableString string];
                           for (NSUInteger i = 0; i < [encoded length]; i+= wrapWidth)
                           {
                               if (i + wrapWidth >= [encoded length])
                               {
                                   [result appendString:[encoded substringFromIndex:i]];
                                   break;
                               }
                               [result appendString:[encoded substringWithRange:NSMakeRange(i, wrapWidth)]];
                               [result appendString:@"\r\n"];
                           }
                           return result;
                       }
                       /**
                        *  @brief  NSData转string 换行长度默认64
                        */
                       - (NSString *)base64EncodedString
                       {
                           return [self base64EncodedStringWithWrapWidth:0];
                       }
                       63、AES加密
                       
#import <CommonCrypto/CommonCryptor.h>
                       @interface NSData (AES)
                       /**
                        *  利用AES加密数据
                        */
                       - (NSData*)encryptedWithAESUsingKey:(NSString*)key andIV:(NSData*)iv {
                           
                           NSData *keyData = [key dataUsingEncoding:NSUTF8StringEncoding];
                           
                           size_t dataMoved;
                           NSMutableData *encryptedData = [NSMutableData dataWithLength:self.length + kCCBlockSizeAES128];
                           
                           CCCryptorStatus status = CCCrypt(kCCEncrypt,kCCAlgorithmAES128,kCCOptionPKCS7Padding,keyData.bytes,keyData.length,iv.bytes,self.bytes,self.length,encryptedData.mutableBytes, encryptedData.length,&dataMoved);
                           
                           if (status == kCCSuccess) {
                               encryptedData.length = dataMoved;
                               return encryptedData;
                           }
                           
                           return nil;
                           
                       }
                       
                       /**
                        *  @brief  利用AES解密据
                        */
                       - (NSData*)decryptedWithAESUsingKey:(NSString*)key andIV:(NSData*)iv {
                           
                           NSData *keyData = [key dataUsingEncoding:NSUTF8StringEncoding];
                           
                           size_t dataMoved;
                           NSMutableData *decryptedData = [NSMutableData dataWithLength:self.length + kCCBlockSizeAES128];
                           
                           CCCryptorStatus result = CCCrypt(kCCDecrypt,kCCAlgorithmAES128,kCCOptionPKCS7Padding,keyData.bytes,keyData.length,iv.bytes,self.bytes,self.length,decryptedData.mutableBytes, decryptedData.length,&dataMoved);
                           
                           if (result == kCCSuccess) {
                               decryptedData.length = dataMoved;
                               return decryptedData;
                           }
                           
                           return nil;
                           
                       }
                       64、3DES加密
                       
#import <CommonCrypto/CommonCryptor.h>
                       @interface NSData (3DES)
                       /**
                        *  利用3DES加密数据
                        */
                       - (NSData*)encryptedWith3DESUsingKey:(NSString*)key andIV:(NSData*)iv {
                           
                           NSData *keyData = [key dataUsingEncoding:NSUTF8StringEncoding];
                           
                           size_t dataMoved;
                           NSMutableData *encryptedData = [NSMutableData dataWithLength:self.length + kCCBlockSize3DES];
                           
                           CCCryptorStatus result = CCCrypt(kCCEncrypt,kCCAlgorithm3DES,kCCOptionPKCS7Padding,keyData.bytes,keyData.length,iv.bytes,self.bytes,self.length,encryptedData.mutableBytes,encryptedData.length,&dataMoved);
                           
                           if (result == kCCSuccess) {
                               encryptedData.length = dataMoved;
                               return encryptedData;
                           }
                           
                           return nil;
                           
                       }
                       /**
                        *  @brief   利用3DES解密数据
                        */
                       - (NSData*)decryptedWith3DESUsingKey:(NSString*)key andIV:(NSData*)iv {
                           
                           NSData *keyData = [key dataUsingEncoding:NSUTF8StringEncoding];
                           
                           size_t dataMoved;
                           NSMutableData *decryptedData = [NSMutableData dataWithLength:self.length + kCCBlockSize3DES];
                           
                           CCCryptorStatus result = CCCrypt(kCCDecrypt,kCCAlgorithm3DES,kCCOptionPKCS7Padding,keyData.bytes,keyData.length,iv.bytes,self.bytes,self.length,decryptedData.mutableBytes,decryptedData.length,&dataMoved);
                           
                           if (result == kCCSuccess) {
                               decryptedData.length = dataMoved;
                               return decryptedData;
                           }
                           
                           return nil;
                           
                       }
                       65、单个页面多个网络请求的情况，需要监听所有网络请求结束后刷新UI
                       
                       dispatch_group_t group = dispatch_group_create();
                       dispatch_queue_t serialQueue = dispatch_queue_create("com.wzb.test.www", DISPATCH_QUEUE_SERIAL);
                       dispatch_group_enter(group);
                       dispatch_group_async(group, serialQueue, ^{
                           // 网络请求一
                           [WebClick getDataSuccess:^(ResponseModel *model) {
                               dispatch_group_leave(group);
                           } failure:^(NSString *err) {
                               dispatch_group_leave(group);
                           }];
                       });
                       dispatch_group_enter(group);
                       dispatch_group_async(group, serialQueue, ^{
                           // 网络请求二
                           [WebClick getDataSuccess:getBigTypeRM onSuccess:^(ResponseModel *model) {
                               dispatch_group_leave(group);
                           }                                  failure:^(NSString *errorString) {
                               dispatch_group_leave(group);
                           }];
                       });
                       dispatch_group_enter(group);
                       dispatch_group_async(group, serialQueue, ^{
                           // 网络请求三
                           [WebClick getDataSuccess:^{
                               dispatch_group_leave(group);
                           } failure:^(NSString *errorString) {
                               dispatch_group_leave(group);
                           }];
                       });
                       
                       // 所有网络请求结束后会来到这个方法
                       dispatch_group_notify(group, serialQueue, ^{
                           dispatch_async(dispatch_get_global_queue(0, 0), ^{
                               dispatch_async(dispatch_get_main_queue(), ^{
                                   // 刷新UI
                               });
                           });
                       });
                       66、解决openUrl延时问题
                       
                       // 方法一
                       dispatch_async(dispatch_get_main_queue(), ^{
                           
                           UIApplication *application = [UIApplication sharedApplication];
                           if ([application respondsToSelector:@selector(openURL:options:completionHandler:)]) {
                               [application openURL:URL options:@{}
                                  completionHandler:nil];
                           } else {
                               [application openURL:URL];
                           }
                       });
                       // 方法二
                       [self performSelector:@selector(redirectToURL:) withObject:url afterDelay:0.1];
                       
                       - (void) redirectToURL
                       {
                           UIApplication *application = [UIApplication sharedApplication];
                           if ([application respondsToSelector:@selector(openURL:options:completionHandler:)]) {
                               [application openURL:URL options:@{}
                                  completionHandler:nil];
                           } else {
                               [application openURL:URL];
                           }
                       }
                       67、页面跳转实现翻转动画
                       
                       // modal方式
                       TestViewController *vc = [[TestViewController alloc] init];
                       vc.view.backgroundColor = [UIColor redColor];
                       vc.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
                       [self presentViewController:vc animated:YES completion:nil];
                       
                       // push方式
                       TestViewController *vc = [[TestViewController alloc] init];
                       vc.view.backgroundColor = [UIColor redColor];
                       [UIView beginAnimations:@"View Flip" context:nil];
                       [UIView setAnimationDuration:0.80];
                       [UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
                       [UIView setAnimationTransition:UIViewAnimationTransitionFlipFromRight forView:self.navigationController.view cache:NO];
                       [self.navigationController pushViewController:vc animated:YES];
                       [UIView commitAnimations];
                       68、tableView实现无限滚动
                       
                       - (void)scrollViewDidScroll:(UIScrollView *)scrollView
                       {
                           CGFloat actualPosition = scrollView.contentOffset.y;
                           CGFloat contentHeight = scrollView.contentSize.height - scrollView.frame.size.height;
                           if (actualPosition >= contentHeight) {
                               [self.dataArr addObjectsFromArray:self.dataArr];
                               [self.tableView reloadData];
                           }
                       }
                       69、代码方式调整屏幕亮度
                       
                       // brightness属性值在0-1之间，0代表最小亮度，1代表最大亮度
                       [[UIScreen mainScreen] setBrightness:0.5];
                       70、获取当前应用CUP用量
                       
                       float cpu_usage()
                       {
                           kern_return_t kr;
                           task_info_data_t tinfo;
                           mach_msg_type_number_t task_info_count;
                           
                           task_info_count = TASK_INFO_MAX;
                           kr = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)tinfo, &task_info_count);
                           if (kr != KERN_SUCCESS) {
                               return -1;
                           }
                           
                           task_basic_info_t      basic_info;
                           thread_array_t         thread_list;
                           mach_msg_type_number_t thread_count;
                           
                           thread_info_data_t     thinfo;
                           mach_msg_type_number_t thread_info_count;
                           
                           thread_basic_info_t basic_info_th;
                           uint32_t stat_thread = 0; // Mach threads
                           
                           basic_info = (task_basic_info_t)tinfo;
                           
                           // get threads in the task
                           kr = task_threads(mach_task_self(), &thread_list, &thread_count);
                           if (kr != KERN_SUCCESS) {
                               return -1;
                           }
                           if (thread_count > 0)
                               stat_thread += thread_count;
                           
                           long tot_sec = 0;
                           long tot_usec = 0;
                           float tot_cpu = 0;
                           int j;
                           
                           for (j = 0; j < (int)thread_count; j++)
                           {
                               thread_info_count = THREAD_INFO_MAX;
                               kr = thread_info(thread_list[j], THREAD_BASIC_INFO,
                                                (thread_info_t)thinfo, &thread_info_count);
                               if (kr != KERN_SUCCESS) {
                                   return -1;
                               }
                               
                               basic_info_th = (thread_basic_info_t)thinfo;
                               
                               if (!(basic_info_th->flags & TH_FLAGS_IDLE)) {
                                   tot_sec = tot_sec + basic_info_th->user_time.seconds + basic_info_th->system_time.seconds;
                                   tot_usec = tot_usec + basic_info_th->user_time.microseconds + basic_info_th->system_time.microseconds;
                                   tot_cpu = tot_cpu + basic_info_th->cpu_usage / (float)TH_USAGE_SCALE * 100.0;
                               }
                               
                           } // for each thread
                           
                           kr = vm_deallocate(mach_task_self(), (vm_offset_t)thread_list, thread_count * sizeof(thread_t));
                           assert(kr == KERN_SUCCESS);
                           
                           return tot_cpu;
                       }
                       71、float数据取整四舍五入
                       
                       CGFloat f = 4.65;
                       NSLog(@"%d", (int)f);    // 打印结果4
                       
                       CGFloat f = 4.65;
                       NSLog(@"%d", (int)round(f));    // 打印结果5
                       72、删除UISearchBar系统默认边框
                       
                       // 方法一
                       searchBar.searchBarStyle = UISearchBarStyleMinimal;
                       
                       // 方法二
                       [searchBar setBackgroundImage:[[UIImage alloc]init]];
                       
                       // 方法三
                       searchBar.barTintColor = [UIColor whiteColor];
                       73、为UICollectionViewCell设置圆角和阴影
                       
                       cell.contentView.layer.cornerRadius = 2.0f;
                       cell.contentView.layer.borderWidth = 1.0f;
                       cell.contentView.layer.borderColor = [UIColor clearColor].CGColor;
                       cell.contentView.layer.masksToBounds = YES;
                       
                       cell.layer.shadowColor = [UIColor lightGrayColor].CGColor;
                       cell.layer.shadowOffset = CGSizeMake(0, 2.0f);
                       cell.layer.shadowRadius = 2.0f;
                       cell.layer.shadowOpacity = 1.0f;
                       cell.layer.masksToBounds = NO;
                       cell.layer.shadowPath = [UIBezierPath bezierPathWithRoundedRect:cell.bounds cornerRadius:cell.contentView.layer.cornerRadius].CGPath;
                       74、让正在滑动的scrollView停止滚动(不是禁止，而是暂时停止滚动)
                       
                       [scrollView setContentOffset:scrollView.contentOffset animated:NO];
                       75、使用xib设置UIView的边框、圆角
                       
                       圆角和边框看下图即可设置
                       
                       xib设置圆角边框.png
                       但是增加layer.borderColor的keyPath设置边框颜色并不能起作用，后来查了资料，这里应该用layer.borderUIColor，但是这里设置的颜色不起作用，无论设置什么颜色显示出来的都是黑色的。后来又去查了下，有种解决方案是给CALayer添加一个分类，提供一个 - (void)setBorderUIColor:(UIColor *)color;方法就可以解决了，实现如下：
                       
                       xib设置边框颜色.png
#import "CALayer+BorderColor.h"
                       
                       @implementation CALayer (BorderColor)
                       
                       - (void)setBorderUIColor:(UIColor *)color
                       {
                           self.borderColor = color.CGColor;
                       }
                       76、根据经纬度获取城市等信息
                       
                       // 创建经纬度
                       CLLocation *location = [[CLLocation alloc] initWithLatitude:latitude longitude:longitude];
                       //创建一个译码器
                       CLGeocoder *cLGeocoder = [[CLGeocoder alloc] init];
                       [cLGeocoder reverseGeocodeLocation:userLocation completionHandler:^(NSArray *placemarks, NSError *error) {
                           CLPlacemark *place = [placemarks objectAtIndex:0];
                           // 位置名
                           　　NSLog(@"name,%@",place.name);
                           　　// 街道
                           　　NSLog(@"thoroughfare,%@",place.thoroughfare);
                           　　// 子街道
                           　　NSLog(@"subThoroughfare,%@",place.subThoroughfare);
                           　　// 市
                           　　NSLog(@"locality,%@",place.locality);
                           　　// 区
                           　　NSLog(@"subLocality,%@",place.subLocality); 
                           　　// 国家
                           　　NSLog(@"country,%@",place.country);
                       }
                        }];
                       
                       /*  CLPlacemark中属性含义
                        name                    地名
                        
                        thoroughfare            街道
                        
                        subThoroughfare        街道相关信息，例如门牌等
                        
                        locality                城市
                        
                        subLocality            城市相关信息，例如标志性建筑
                        
                        administrativeArea      直辖市
                        
                        subAdministrativeArea  其他行政区域信息（自治区等）
                        
                        postalCode              邮编
                        
                        ISOcountryCode          国家编码
                        
                        country                国家
                        
                        inlandWater            水源，湖泊
                        
                        ocean                  海洋
                        
                        areasOfInterest        关联的或利益相关的地标
                        */
                       77、如何防止添加多个NSNotification观察者？
                       
                       // 解决方案就是添加观察者之前先移除下这个观察者
                       [[NSNotificationCenter defaultCenter] removeObserver:observer name:name object:object];
                       [[NSNotificationCenter defaultCenter] addObserver:observer selector:selector name:name object:object];
                       78、将一个xib添加到另外一个xib上
                       
                       // 假设你的自定义view名字为CustomView，你需要在CustomView.m中重写 `- (instancetype)initWithCoder:(NSCoder *)aDecoder` 方法，代码如下：
                       - (instancetype)initWithCoder:(NSCoder *)aDecoder {
                           if ((self = [super initWithCoder:aDecoder])) {
                               [self addSubview:[[[NSBundle mainBundle] loadNibNamed:@"CustomView" owner:self options:nil] objectAtIndex:0]];
                           }
                           return self;
                       }
                       
                       将一个xib添加到另外一个xib上.png
                       79、处理字符串，使其首字母大写
                       
                       NSString *str = @"abcdefghijklmn";
                       NSString *resultStr;
                       if (str && str.length > 0) {
                           resultStr = [str stringByReplacingCharactersInRange:NSMakeRange(0,1) withString:[[str substringToIndex:1] capitalizedString]];
                       }
                       NSLog(@"%@", resultStr);
                       80、判断一个UIAlertView/UIAlertController是否显示
                       
                       // UIAlertView自带属性
                       if (alert.visible)
                       {
                           NSLog(@"显示了");
                       } else {
                           NSLog(@"未显示");
                       }
                       
                       // UIAlertController没有visible属性，需要自己判断，添加一个全局变量 BOOL visible
                       UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Title" message:@"message" preferredStyle:UIAlertControllerStyleAlert];
                       UIAlertAction *alertAction = [UIAlertAction actionWithTitle:@"ActionTitle" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                           self.visible = NO;
                       }];
                       UIAlertAction *calcelAction = [UIAlertAction actionWithTitle:@"calcelTitle" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
                           self.visible = NO;
                       }];
                       [alertController addAction:alertAction];
                       [alertController addAction:calcelAction];
                       [self presentViewController:alertController animated:YES completion:^{
                           self.visible = YES;
                       }];
                       81、获取字符串中的数字
                       
                       - (NSString *)getNumberFromStr:(NSString *)str
                       {
                           NSCharacterSet *nonDigitCharacterSet = [[NSCharacterSet decimalDigitCharacterSet] invertedSet];
                           return [[str componentsSeparatedByCharactersInSet:nonDigitCharacterSet] componentsJoinedByString:@""];
                       }
                       
                       NSLog(@"%@", [self getNumberFromStr:@"a0b0c1d2e3f4fda8fa8fad9fsad23"]); // 00123488923
                       82、为UIView的某个方向添加边框
                       
                       // 添加UIView分类
                       
                       // UIView+WZB.h
#import <UIKit/UIKit.h>
                       
                       
                       /**
                        边框方向
                        
                        - WZBBorderDirectionTop: 顶部
                        - WZBBorderDirectionLeft: 左边
                        - WZBBorderDirectionBottom: 底部
                        - WZBBorderDirectionRight: 右边
                        */
                       typedef NS_ENUM(NSInteger, WZBBorderDirectionType) {
                           WZBBorderDirectionTop = 0,
                           WZBBorderDirectionLeft,
                           WZBBorderDirectionBottom,
                           WZBBorderDirectionRight
                       };
                       
                       @interface UIView (WZB)
                       
                       
                       /**
                        为UIView的某个方向添加边框
                        
                        @param direction 边框方向
                        @param color 边框颜色
                        @param width 边框宽度
                        */
                       - (void)wzb_addBorder:(WZBBorderDirectionType)direction color:(UIColor *)color width:(CGFloat)width;
                       
                       @end
                       
                       // UIView+WZB.m
#import "UIView+WZB.h"
                       
                       @implementation UIView (WZB)
                       
                       - (void)wzb_addBorder:(WZBBorderDirectionType)direction color:(UIColor *)color width:(CGFloat)width
                       {
                           CALayer *border = [CALayer layer];
                           border.backgroundColor = color.CGColor;
                           switch (direction) {
                               case WZBBorderDirectionTop:
                               {
                                   border.frame = CGRectMake(0.0f, 0.0f, self.bounds.size.width, width);
                               }
                                   break;
                               case WZBBorderDirectionLeft:
                               {
                                   border.frame = CGRectMake(0.0f, 0.0f, width, self.bounds.size.height);
                               }
                                   break;
                               case WZBBorderDirectionBottom:
                               {
                                   border.frame = CGRectMake(0.0f, self.bounds.size.height - width, self.bounds.size.width, width);
                               }
                                   break;
                               case WZBBorderDirectionRight:
                               {
                                   border.frame = CGRectMake(self.bounds.size.width - width, 0, width, self.bounds.size.height);
                               }
                                   break;
                                   
                               default:
                                   break;
                           }
                           [self.layer addSublayer:border];
                       }
                       83、通过属性设置UISwitch、UIProgressView等控件的宽高
                       
                       mySwitch.transform = CGAffineTransformMakeScale(5.0f, 5.0f);
                       
                       progressView.transform = CGAffineTransformMakeScale(5.0f, 5.0f);
                       84、自动搜索功能，用户连续输入的时候不搜索，用户停止输入的时候自动搜索(我这里设置的是0.5s，可根据需求更改)
                       
                       // 输入框文字改变的时候调用
                       -(void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText{
                           // 先取消调用搜索方法
                           [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(searchNewResult) object:nil];
                           // 0.5秒后调用搜索方法
                           [self performSelector:@selector(searchNewResult) withObject:nil afterDelay:0.5];
                       }
                       85、修改UISearchBar的占位文字颜色
                       
                       // 方法一（推荐使用）
                       UITextField *searchField = [searchBar valueForKey:@"_searchField"];
                       [searchField setValue:[UIColor blueColor] forKeyPath:@"_placeholderLabel.textColor"];
                       
                       // 方法二（已过期）
                       [[UILabel appearanceWhenContainedIn:[UISearchBar class], nil] setTextColor:[UIColor redColor]];
                       
                       // 方法三（已过期）
                       NSDictionary *placeholderAttributes = @{NSForegroundColorAttributeName : [UIColor redColor], NSFontAttributeName : [UIFont fontWithName:@"HelveticaNeue" size:15],};
                       NSAttributedString *attributedPlaceholder = [[NSAttributedString alloc] initWithString:searchBar.placeholder attributes:placeholderAttributes];
                       [[UITextField appearanceWhenContainedIn:[UISearchBar class], nil] setAttributedPlaceholder:attributedPlaceholder];
                       86、某个界面多个事件同时响应引起的问题(比如，两个button同时按push到新界面，两个都会响应，可能导致push重叠)
                       
                       // UIView有个属性叫做exclusiveTouch，设置为YES后，其响应事件会和其他view互斥(有其他view事件响应的时候点击它不起作用)
                       view.exclusiveTouch = YES;
                       
                       // 一个一个设置太麻烦了，可以全局设置
                       [[UIView appearance] setExclusiveTouch:YES];
                       
                       // 或者只设置button
                       [[UIButton appearance] setExclusiveTouch:YES];
                       87、修改tabBar的frame
                       
                       // 子类化UITabBarViewController，我这里以修改tabBar高度为例，重写viewWillLayoutSubviews方法
#import "WZBTabBarViewController.h"
                       
                       @interface WZBTabBarViewController ()
                       
                       @end
                       
                       @implementation WZBTabBarViewController
                       - (void)viewWillLayoutSubviews {
                           
                           CGRect tabFrame = self.tabBar.frame;
                           tabFrame.size.height = 100;
                           tabFrame.origin.y = self.view.frame.size.height - 100;
                           self.tabBar.frame = tabFrame;
                       }
                       @end
                       88、修改键盘背景颜色
                       
                       // 设置某个键盘颜色
                       textField.keyboardAppearance = UIKeyboardAppearanceAlert;
                       
                       // 设置工程中所有键盘颜色
                       [[UITextField appearance] setKeyboardAppearance:UIKeyboardAppearanceAlert];
                       89、修改image颜色
                       
                       UIImage *image = [UIImage imageNamed:@"test"];
                       imageView.image = [image imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
                       CGRect rect = CGRectMake(0, 0, image.size.width, image.size.height);
                       UIGraphicsBeginImageContext(rect.size);
                       CGContextRef context = UIGraphicsGetCurrentContext();
                       CGContextClipToMask(context, rect, image.CGImage);
                       CGContextSetFillColorWithColor(context, [[UIColor redColor] CGColor]);
                       CGContextFillRect(context, rect);
                       UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
                       UIGraphicsEndImageContext();
                       
                       UIImage *flippedImage = [UIImage imageWithCGImage:img.CGImage scale:1.0 orientation: UIImageOrientationDownMirrored];
                       imageView.image = flippedImage;
                       90、动画执行removeFromSuperview
                       
                       [UIView animateWithDuration:0.2
                                        animations:^{
                                            view.alpha = 0.0f;
                                        } completion:^(BOOL finished){
                                            [view removeFromSuperview];
                                        }];
                       91、启动页显示延时
                       
                       - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
                       {
                           //  延时10s
                           sleep(10);
                           return YES;
                       }
                       92、设置UIButton高亮时的背景颜色
                       
                       // 方法一、子类化UIButton，重写setHighlighted:方法，代码如下
#import "WZBButton.h"
                       
                       @implementation WZBButton
                       
                       - (void)setHighlighted:(BOOL)highlighted {
                           [super setHighlighted:highlighted];
                           
                           UIColor *normalColor = [UIColor greenColor];
                           UIColor *highlightedColor = [UIColor redColor];
                           self.backgroundColor = highlighted ? highlightedColor : normalColor;
                           
                       }
                       
                       // 方法二、利用setBackgroundImage:forState:方法
                       [button setBackgroundImage:[self imageWithColor:[UIColor blueColor]] forState:UIControlStateHighlighted];
                       
                       - (UIImage *)imageWithColor:(UIColor *)color {
                           CGRect rect = CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
                           UIGraphicsBeginImageContext(rect.size);
                           CGContextRef context = UIGraphicsGetCurrentContext();
                           
                           CGContextSetFillColorWithColor(context, [color CGColor]);
                           CGContextFillRect(context, rect);
                           
                           UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
                           UIGraphicsEndImageContext();
                           
                           return image;
                       }
                       93、关于图片拉伸
                       
                       推荐看这个博客，讲的很详细http://blog.csdn.net/q199109106q/article/details/8615661
                       94、利用runtime获取一个类所有属性
                       
                       - (NSArray *)allPropertyNames:(Class)aClass
                       {
                           unsigned count;
                           objc_property_t *properties = class_copyPropertyList(aClass, &count);
                           
                           NSMutableArray *rv = [NSMutableArray array];
                           
                           unsigned i;
                           for (i = 0; i < count; i++)
                           {
                               objc_property_t property = properties[i];
                               NSString *name = [NSString stringWithUTF8String:property_getName(property)];
                               [rv addObject:name];
                           }
                           
                           free(properties);
                           
                           return rv;
                       }
                       95、设置textView的某段文字变成其他颜色
                       
                       - (void)setupTextView:(UITextView *)textView text:(NSString *)text color:(UIColor *)color {
                           NSMutableAttributedString *string = [[NSMutableAttributedString alloc]initWithString:textView.text];
                           [string addAttribute:NSForegroundColorAttributeName value:color range:[textView.text rangeOfString:text]];
                           [textView setAttributedText:string];
                       }
                       96、让push跳转动画像modal跳转动画那样效果(从下往上推上来)
                       
                       - (void)push
                       {
                           TestViewController *vc = [[TestViewController alloc] init];
                           vc.view.backgroundColor = [UIColor redColor];
                           CATransition* transition = [CATransition animation];
                           transition.duration = 0.4f;
                           transition.type = kCATransitionMoveIn;
                           transition.subtype = kCATransitionFromTop;
                           [self.navigationController.view.layer addAnimation:transition forKey:kCATransition];
                           [self.navigationController pushViewController:vc animated:NO];
                       }
                       
                       - (void)pop
                       {
                           CATransition* transition = [CATransition animation];
                           transition.duration = 0.4f;
                           transition.type = kCATransitionReveal;
                           transition.subtype = kCATransitionFromBottom;
                           [self.navigationController.view.layer addAnimation:transition forKey:kCATransition];
                           [self.navigationController popViewControllerAnimated:NO];
                       }
                       97、上传图片太大，压缩图片
                       
                       -(UIImage *)resizeImage:(UIImage *)image
                       {
                           float actualHeight = image.size.height;
                           float actualWidth = image.size.width;
                           float maxHeight = 300.0;
                           float maxWidth = 400.0;
                           float imgRatio = actualWidth/actualHeight;
                           float maxRatio = maxWidth/maxHeight;
                           float compressionQuality = 0.5;//50 percent compression
                           
                           if (actualHeight > maxHeight || actualWidth > maxWidth)
                           {
                               if(imgRatio < maxRatio)
                               {
                                   //adjust width according to maxHeight
                                   imgRatio = maxHeight / actualHeight;
                                   actualWidth = imgRatio * actualWidth;
                                   actualHeight = maxHeight;
                               }
                               else if(imgRatio > maxRatio)
                               {
                                   //adjust height according to maxWidth
                                   imgRatio = maxWidth / actualWidth;
                                   actualHeight = imgRatio * actualHeight;
                                   actualWidth = maxWidth;
                               }
                               else
                               {
                                   actualHeight = maxHeight;
                                   actualWidth = maxWidth;
                               }
                           }
                           
                           CGRect rect = CGRectMake(0.0, 0.0, actualWidth, actualHeight);
                           UIGraphicsBeginImageContext(rect.size);
                           [image drawInRect:rect];
                           UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
                           NSData *imageData = UIImageJPEGRepresentation(img, compressionQuality);
                           UIGraphicsEndImageContext();
                           
                           return [UIImage imageWithData:imageData];
                           
                       }
