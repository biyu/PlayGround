.pragma library
// common page constants
var Page_Width = 480;
var Page_Height = 854;
var Page_Common_Font_Family = "Nokia Pure";
var Page_Common_Font_Family_Bold = "Nokia Pure Bold";
var Page_Common_Font_Family_Light = "Nokia Pure Light";
var Page_Common_Font_PixelSize = 25;
var Page_ToolBar_Font_PixelSize = 40;
var Page_Common_ListView_MaximumFlickVelocity = 20;
var Page_Common_Text_Color = "white";

// errors
var Page_Common_Error_No_Location_Info = 1;

// page names
var QuickRoutePlanPage_Name = "HSLJP";
var RouteResultPage_Name = "Results";
var StartPointSelectPage_Name = "Point of Origin";

// destination picker constants
var DestinationPicker_Width = Page_Width-15;
var DestinationPicker_Height = Page_Height/2;

var DestinationPicker_Delegate_Width = DestinationPicker_Width;
var DestinationPicker_Delegate_Height = DestinationPicker_Height/7;

var DestinationPicker_Delegate_Highlight_Width = DestinationPicker_Delegate_Width;
var DestinationPicker_Delegate_Highlight_Height = DestinationPicker_Delegate_Height;
var DestinationPicker_Delegate_Highlight_Begin = (DestinationPicker_Height - DestinationPicker_Delegate_Height)/2;
var DestinationPicker_Delegate_Highlight_End = (DestinationPicker_Height + DestinationPicker_Delegate_Height)/2;
var DestinationPicker_Delegate_Highlight_Border_Width = 2;
var DestinationPicker_Delegate_Highlight_Opacity = 0.3;

var DestinationPicker_Delegate_Font_Family = Page_Common_Font_Family;
var DestinationPicker_Delegate_Font_PixelSize = DestinationPicker_Delegate_Height*0.5;
var DestinationPicker_Delegate_Font_WordSpace = 0;

var DestinationPicker_Soundeffect_Filename = "SoundEffects/scrolleffect.wav";

// select button
var SelectButton_Width = Page_Width-60;
var SelectButton_Height = Page_Height/8;
var SelectButton_Text_New = "Continue";
var SelectButton_Text_FindRoute = "Find Route";
var SelectButton_Anchor_TopMargin = 15;

var SelectButton_Font_Family = Page_Common_Font_Family;
var SelectButton_Font_PixelSize = SelectButton_Height*0.4;
var SelectButton_Font_WordSpace = 0;

// start-point picker
var StartPointPicker_Width = Page_Width-15;
var StartPointPicker_Height = Page_Height/9;
var StartPointPicker_BottomMargin = 20;

var StartPointPicker_Default_Text = "[Current Location]";
var StartPointPicker_Prefix_Text = "From:";

var StartPointPicker_Text_Item_Width = StartPointPicker_Width;
var StartPointPicker_Text_Item_Height = StartPointPicker_Height*0.3;
var StartPointPicker_Prefix_Text_Width = StartPointPicker_Text_Item_Width/5;
var StartPointPicker_Prefix_Text_Height = StartPointPicker_Text_Item_Height;
var StartPointPicker_Prefix_Text_LeftMargin = 10;
var StartPointPicker_Address_Text_Width = StartPointPicker_Text_Item_Width*27/40;
var StartPointPicker_Address_Text_Height = StartPointPicker_Text_Item_Height;
var StartPointPicker_Address_Text_LeftMargin = 10;
var StartPointPicker_MoreIndicator_Width = StartPointPicker_Text_Item_Width/8;
var StartPointPicker_MoreIndicator_Height = StartPointPicker_Text_Item_Height;
var StartPointPicker_Font_PixelSize = StartPointPicker_Text_Item_Height*0.9;

// route results list
var RouteResultList_Width = Page_Width-15;
var RouteResultList_Height = Page_Height*0.8;
var RouteResultList_List_TopMargin = 30;
var RouteResultList_Header_Width = RouteResultList_Width;
var RouteResultList_Header_Height = RouteResultList_Height/10;
var RouteResultList_Header_Color = "gray";
var RouteResultList_Header_Opacity = 0.2;
var RouteResultList_Header_Text_Color = "white";
var RouteResultList_Header_Text_Delimeter = " => "
var RouteResultList_Header_Text_Font_PixelSize = 25;
var RouteResultList_Delegate_Width = RouteResultList_Width;
var RouteResultList_Delegate_Height = RouteResultList_Height/7;
var RouteResultList_Delegate_ImageSource_Walk = "Images/walk.gif";
var RouteResultList_Delegate_ImageSource_Bus = "Images/bus.gif";
var RouteResultList_Delegate_ImageSource_Metro = "Images/metro.gif";
var RouteResultList_Delegate_ImageSource_Tram = "Images/tram.gif"
var RouteResultList_Delegate_ImageSource_Train = "Images/train.gif"

// line edit
var LineEdit_Label_LeftMargin = 10;

// switcher
var Switcher_Label_LeftMergin = 10;
var Switcher_Switch_RightMergin = 20;

// new destination sheet
var NewDestinationSheet_Component_Height_Ratio = 1/11;

// start point select page
var StartPointSelectPage_Button_Width = Page_Width-30;
var StartPointSelectPage_Button_Height = Page_Height/9;
var StartPointSelectPage_TopMargin = Page_Height/10;
var StartPointSelectPage_Title_Text = "Select Point of Origin"
