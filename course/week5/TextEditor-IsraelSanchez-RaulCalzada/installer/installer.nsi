Name "TextEditor"

OutFile "texteditor-installer.exe"

DirText "TextEditor is a small text editor made with Qt Creator. To install in a different folder, click browse and select another folder." \
  "Destination folder"

InstallDir "$DESKTOP\TextEditor"

RequestExecutionLevel user

Section
	SetOutPath       "$INSTDIR"
	File             "TextEditor.exe"
	WriteUninstaller "$INSTDIR\uninstall.exe"
	CreateShortCut   "$DESKTOP\TextEditor.lnk" "$INSTDIR\TextEditor.exe"
	CreateShortCut   "$DESKTOP\uninstall.lnk"  "$INSTDIR\uninstall.exe"
SectionEnd

Section "uninstall"
	Delete "$DESKTOP\TextEditor.lnk"
	Delete "$DESKTOP\uninstall.lnk"
	Delete "$INSTDIR\TextEditor.exe"
	Delete "$INSTDIR\uninstall.exe"
	RMDir  "$INSTDIR"
SectionEnd
