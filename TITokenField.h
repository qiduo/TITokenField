//
//  TITokenField.h
//  TITokenField
//
//  Created by Tom Irving on 16/02/2010.
//  Copyright 2012 Tom Irving. All rights reserved.
//
//	Redistribution and use in source and binary forms, with or without modification,
//	are permitted provided that the following conditions are met:
//
//		1. Redistributions of source code must retain the above copyright notice, this list of
//		   conditions and the following disclaimer.
//
//		2. Redistributions in binary form must reproduce the above copyright notice, this list
//         of conditions and the following disclaimer in the documentation and/or other materials
//         provided with the distribution.
//
//	THIS SOFTWARE IS PROVIDED BY TOM IRVING "AS IS" AND ANY EXPRESS OR IMPLIED
//	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//	FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TOM IRVING OR
//	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//	ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import <UIKit/UIKit.h>

@class TITokenField, TIToken;

//==========================================================
#pragma mark - Delegate Methods -
//==========================================================
@protocol TITokenFieldDelegate <UITextFieldDelegate>
@optional
- (BOOL)tokenField:(TITokenField *)tokenField willAddToken:(TIToken *)token;
- (void)tokenField:(TITokenField *)tokenField didAddToken:(TIToken *)token;
- (BOOL)tokenField:(TITokenField *)tokenField willRemoveToken:(TIToken *)token;
- (void)tokenField:(TITokenField *)tokenField didRemoveToken:(TIToken *)token;

- (void)tokenField:(TITokenField *)tokenField didTouchToken:(TIToken *)token;
- (BOOL)tokenField:(TITokenField *)tokenField shouldSelectToken:(TIToken *)token;
- (void)tokenField:(TITokenField *)tokenField didSelectToken:(TIToken *)token;

- (void)tokenField:(TITokenField *)tokenField didFinishSearch:(NSArray *)matches;
- (NSString *)tokenField:(TITokenField *)tokenField displayStringForRepresentedObject:(id)object;
- (NSString *)tokenField:(TITokenField *)tokenField searchResultStringForRepresentedObject:(id)object;
- (NSString *)tokenField:(TITokenField *)tokenField searchResultSubtitleForRepresentedObject:(id)object;
- (UITableViewCell *)tokenField:(TITokenField *)tokenField resultsTableView:(UITableView *)tableView cellForRepresentedObject:(id)object;
- (CGFloat)tokenField:(TITokenField *)tokenField resultsTableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
@end

@interface TITokenFieldInternalDelegate : NSObject <UITextFieldDelegate>
@end

//==========================================================
#pragma mark - TITokenFieldView -
//==========================================================
@interface TITokenFieldView : UIScrollView <UITableViewDelegate, UITableViewDataSource, TITokenFieldDelegate>
@property (nonatomic, assign) BOOL showAlreadyTokenized;
@property (nonatomic, assign) BOOL searchSubtitles;
@property (nonatomic, assign) BOOL forcePickSearchResult;
@property (nonatomic, readonly) TITokenField * tokenField;
@property (nonatomic, readonly) UIView * separator;
@property (nonatomic, readonly) UITableView * resultsTable;
@property (nonatomic, readonly) UIView * contentView;
@property (nonatomic, copy) NSArray * sourceArray;
@property (weak, nonatomic, readonly) NSArray * tokenTitles;

- (void)updateContentSize;

@end

//==========================================================
#pragma mark - TITokenField -
//==========================================================
typedef enum {
	TITokenFieldControlEventFrameWillChange = 1 << 24,
	TITokenFieldControlEventFrameDidChange = 1 << 25,
} TITokenFieldControlEvents;

@interface TITokenField : UITextField
@property (nonatomic, weak) id <TITokenFieldDelegate> delegate;
@property (weak, nonatomic, readonly) NSArray * tokens;
@property (weak, nonatomic, readonly) TIToken * selectedToken;
@property (weak, nonatomic, readonly) NSArray * tokenTitles;
@property (weak, nonatomic, readonly) NSArray * tokenObjects;
@property (nonatomic, assign) BOOL editable;
@property (nonatomic, assign) BOOL resultsModeEnabled;
@property (nonatomic, assign) BOOL removesTokensOnEndEditing;
@property (nonatomic, assign) BOOL becomesFirstResponderOnAddingToken;
@property (nonatomic, assign) CGFloat minimumRightPadding;
@property (nonatomic, assign) CGFloat tokenMargin;
@property (nonatomic, assign) CGFloat topLineHeightAdjustment;
@property (nonatomic, assign) UIEdgeInsets insets;
@property (nonatomic, readonly) int numberOfLines;
@property (nonatomic, strong) NSCharacterSet * tokenizingCharacters;

- (void)addToken:(TIToken *)title;
- (TIToken *)addTokenWithTitle:(NSString *)title;
- (TIToken *)addTokenWithTitle:(NSString *)title representedObject:(id)object;
- (void)removeToken:(TIToken *)token;
- (void)removeAllTokens;

- (void)selectToken:(TIToken *)token;
- (void)deselectSelectedToken;

- (void)tokenizeText;

- (void)layoutTokensAnimated:(BOOL)animated;
- (void)setResultsModeEnabled:(BOOL)enabled animated:(BOOL)animated;

// Pass nil to hide label
- (void)setPromptText:(NSString *)aText;

@end

//==========================================================
#pragma mark - TIToken -
//==========================================================
typedef enum {
	TITokenAccessoryTypeNone = 0, // Default
	TITokenAccessoryTypeDisclosureIndicator = 1,
} TITokenAccessoryType;

typedef enum {
    TITokenUnderlineTypeSolid,
	TITokenUnderlineTypeDashed,
} TITokenUnderlineType;

@interface TIToken : UIControl
@property (nonatomic, copy) NSString * title;
@property (nonatomic, copy) NSString * superscript;
@property (nonatomic, strong) id representedObject;
@property (nonatomic, strong) UIFont * font;
@property (nonatomic, strong) UIFont * superscriptFont;
@property (nonatomic, assign) UIOffset superscriptPositionAdjustment;
@property (nonatomic, strong) UIColor * tintColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, strong) UIColor * textColor;
@property (nonatomic, strong) UIColor * superscriptTextColor;
@property (nonatomic, strong) UIColor * highlightedTextColor;
@property (nonatomic, assign) UIOffset textPositionAdjustment;
@property (nonatomic, assign) TITokenAccessoryType accessoryType;
@property (nonatomic, assign) TITokenUnderlineType underlineType;
@property (nonatomic, assign) CGFloat underlineWidth;
@property (nonatomic, assign) CGFloat maxWidth;
@property (nonatomic, assign) CGFloat maxSuperscriptWidth;
@property (nonatomic, assign) BOOL showsBackground;
@property (nonatomic, assign) BOOL adjustsTextWhenHighlighted;
@property (nonatomic, assign) CGFloat verticalTextPadding;
@property (nonatomic, assign) CGFloat horizontalTextPadding;

- (id)initWithTitle:(NSString *)aTitle;
- (id)initWithTitle:(NSString *)aTitle representedObject:(id)object;
- (id)initWithTitle:(NSString *)aTitle representedObject:(id)object font:(UIFont *)aFont;

+ (UIColor *)blueTintColor;
+ (UIColor *)redTintColor;
+ (UIColor *)greenTintColor;

@end