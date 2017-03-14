//
//  SSMoveAction.h
//  testPCEvent
//
//  Created by weizhiqiangzz on 12-12-24.
//  Copyright (c) 2012年 weizhiqiangzz. All rights reserved.
//

#import "SSAction.h"

@interface SSMoveAction : SSAction

-(SSMoveAction*) initWithInfo:(UIView<ActionOperator>*)targetView
                  withCurTransform:(CGAffineTransform)_curTransform
                  withPrevTransform:(CGAffineTransform)_prevTransform;

@property(nonatomic) float fTxFromPrevToCur;
@property(nonatomic) float fTyFromPrevToCur;

@end
