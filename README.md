# Image and AVI Capture
This programming example shows how to capture AVI files and JPEG images using IC Imaging Control simultaneously.
This problem is solved using a special frame filter that saves images to JPEG files. The frame filter is included in the sample's setup file. Following functionallity is implemented in the sample:
- Open and setup a video capture device using IC Imaging Control's built-in dialogs.
- Save the currently used video capture and load the last used video capture device at program start.
- Resize the live video to IC Imaging Control's window size.
- List all available codecs in a combo box.
- If available, then show the codec's property dialog.
- Pause and continue AVI Capture.
- Snap and save images while AVI files are captured.

![alt tag](https://raw.githubusercontent.com/TheImagingSource/Windows-Sample-Image-and-AVI-Capture/master/imageavicapture.png)

Most of the listed tasks are explained in the other samples of the code library. Thus only the use of the "Save Image" frame filter will be explained. First of all a variable of type TIS.Imaging.FrameFilter is to be declared on top of the form. This variable is named SnapImageFilter and will be used for accessing the frame filter for image saving.

The "Save Image" filter will be loaded in the Form1_load< sub. After it has been tried to load  the filter, the content of SnapImageFilter is checked whether it is Nothin. If SnapImageFilter is Nothing, the filter has not been loaded. This happens,
if the filter file SaveImageFrameFilter.FTF is not located in the application's path. 
The frame filter is added to the solution. Its action property is set tp "Copy if newer", so the frame filter is copied
to the application.

The parameter "ImageName" of the SnapImageFilter must be set to a valid
file name. This causes the SnapImageFilter to save an image. Since this is a parameter transfer
between the application's thread and the IC Imaging Control video thread, this must be set into BeginParameterTransfer
and EndParameterTransfer calls. The SnapImageFilter will capture the next incoming
image after the parameter "ImageName" has been set.
