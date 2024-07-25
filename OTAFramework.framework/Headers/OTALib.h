//
//  OTALib.h
//  OTAFramework
//
//  Created by BlackMac on 2017/12/1.
//  Copyright © 2017年 HunterSun. All rights reserved.
//


#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger,typeCode) {
    // file type
    APP_TYPE = 0,
    CONFG_TYPE = 1,
    PATCH_TYPE = 2,
    // charac type
    CMD_CHARC_INTERVAL_TYPE = 3,
    CMD_CHARC_TYPE = 4,
    DAT_CHARC_TYPE = 5,
    CMD_CHARC_NONOTIFY_TYPE = 6,
    // isp type
    ISP_ADDR = 7,
    ENTRY_ISP = 8
};

//// file type
//const int  = 0;
//const int CONFG_TYPE = 1;
//const int PATCH_TYPE = 2;
//// charc type
//const int CMD_CHARC_TYPE = 4;
//const int DAT_CHARC_TYPE = 5;
//const int CMD_CHARC_NONOTIFY_TYPE = 6;
//// isp type
//const int ISP_ADDR = 7;
//const int ENTRY_ISP = 8;

@protocol OtaDelegate <NSObject>
// loadBinary包装数据通过代理回传给VC type:4 cmd charc 发送数据; 5  dat charc 发送数据
@required
-(void)packetDataCallBack:(NSMutableData *)data charcType:(typeCode)charcType;

// 回传文件发送的进度，实现UI进度更新
@required
-(void)progressCallBack:(float)progress;

@optional
// 回传读地址的数据
-(void)readAddrCallBack:(typeCode)type Addr:(int)addr Length:(int)length;
@end

@interface OTALib : NSObject
// delegate
@property(nonatomic,weak)id<OtaDelegate> delegate;

// 设置是否进行加密传输，如果true，则通过packetDataCallBack返回，需要发送给cmdCharc特征的数据
-(void)setEncrypt:(BOOL)isEncrypt;
// 发送用户的自己的数据，可以将数据烧到指定的位置
-(int)writeUserData:(NSMutableData*)fileData addr:(int)addr;
// 对将要发送的文件数据进行包装,包装后的数据通过packetDataCallBack返回给客户端，发送给datCharc特征
-(int)loadBinary:(NSMutableData*)fileData fileType:(typeCode)fileType;
// 读取指定分区的地址
-(int)readPartitionAddr:(typeCode)partType;
// 一键进入ISP模式
-(void)entryIspMoudle:(typeCode)type;
// 执行复位操作
-(void)resetTarget;
// 将蓝牙返回的数据，发送给库 type:0 cmd charc 特征返回的值; 1  dat charc特征返回的值
-(void)setBluetoothNotifyData:(NSMutableData*)data charcType:(typeCode)charcType;

@end
