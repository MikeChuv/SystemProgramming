object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = #1051#1072#1073#1086#1088#1072#1090#1086#1088#1085#1072#1103' '#1088#1072#1073#1086#1090#1072' '#8470'4'
  ClientHeight = 595
  ClientWidth = 1061
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnPaint = FormPaint
  OnResize = FormResize
  DesignSize = (
    1061
    595)
  PixelsPerInch = 96
  TextHeight = 19
  object btnPicture: TButton
    Left = 8
    Top = 546
    Width = 177
    Height = 40
    Anchors = [akLeft, akBottom]
    Caption = #1053#1072#1088#1080#1089#1086#1074#1072#1090#1100' '#1082#1072#1088#1090#1080#1085#1082#1091
    TabOrder = 0
    OnClick = btnPictureClick
  end
  object btnRandomBackground: TButton
    Left = 514
    Top = 548
    Width = 177
    Height = 39
    Anchors = [akRight, akBottom]
    Caption = #1047#1072#1083#1080#1090#1100' '#1074#1089#1077
    TabOrder = 1
    OnClick = btnRandomBackgroundClick
  end
  object btnRandomRect: TButton
    Left = 713
    Top = 548
    Width = 170
    Height = 39
    Anchors = [akRight, akBottom]
    Caption = #1055#1088#1103#1084#1086#1091#1075#1086#1083#1100#1085#1080#1082
    TabOrder = 2
    OnClick = btnRandomRectClick
  end
  object btnCircle: TButton
    Left = 896
    Top = 548
    Width = 153
    Height = 39
    Anchors = [akRight, akBottom]
    Caption = #1050#1088#1091#1075
    TabOrder = 3
    OnClick = btnCircleClick
  end
end
