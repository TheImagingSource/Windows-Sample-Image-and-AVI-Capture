Public Class Form1
    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents IcImagingControl1 As TIS.Imaging.ICImagingControl
    Friend WithEvents btnDevice As System.Windows.Forms.Button
    Friend WithEvents btnSettings As System.Windows.Forms.Button
    Friend WithEvents btnStartStop As System.Windows.Forms.Button
    Friend WithEvents btnSnapImage As System.Windows.Forms.Button
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents cboCodecs As System.Windows.Forms.ComboBox
    Friend WithEvents btnCodecProperties As System.Windows.Forms.Button
    Friend WithEvents chkAVIPause As System.Windows.Forms.CheckBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.IcImagingControl1 = New TIS.Imaging.ICImagingControl
        Me.btnDevice = New System.Windows.Forms.Button
        Me.btnSettings = New System.Windows.Forms.Button
        Me.btnStartStop = New System.Windows.Forms.Button
        Me.btnSnapImage = New System.Windows.Forms.Button
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.btnCodecProperties = New System.Windows.Forms.Button
        Me.cboCodecs = New System.Windows.Forms.ComboBox
        Me.chkAVIPause = New System.Windows.Forms.CheckBox
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'IcImagingControl1
        '
        Me.IcImagingControl1.DeBayerMode = TIS.Imaging.DeBayerModes.Edgesensing
        Me.IcImagingControl1.DeBayerStartPattern = TIS.Imaging.DeBayerStartPatterns.BG
        Me.IcImagingControl1.ImageRingBufferSize = 5
        Me.IcImagingControl1.LiveDisplayHeight = 480
        Me.IcImagingControl1.LiveDisplayWidth = 640
        Me.IcImagingControl1.LiveShowLastBuffer = True
        Me.IcImagingControl1.Location = New System.Drawing.Point(8, 8)
        Me.IcImagingControl1.Name = "IcImagingControl1"
        Me.IcImagingControl1.OverlayBitmapPosition = TIS.Imaging.PathPositions.Device
        Me.IcImagingControl1.Size = New System.Drawing.Size(312, 248)
        Me.IcImagingControl1.TabIndex = 0
        '
        'btnDevice
        '
        Me.btnDevice.Location = New System.Drawing.Point(336, 8)
        Me.btnDevice.Name = "btnDevice"
        Me.btnDevice.Size = New System.Drawing.Size(72, 24)
        Me.btnDevice.TabIndex = 1
        Me.btnDevice.Text = "Device"
        '
        'btnSettings
        '
        Me.btnSettings.Location = New System.Drawing.Point(416, 8)
        Me.btnSettings.Name = "btnSettings"
        Me.btnSettings.Size = New System.Drawing.Size(72, 24)
        Me.btnSettings.TabIndex = 2
        Me.btnSettings.Text = "Settings"
        '
        'btnStartStop
        '
        Me.btnStartStop.Location = New System.Drawing.Point(336, 40)
        Me.btnStartStop.Name = "btnStartStop"
        Me.btnStartStop.Size = New System.Drawing.Size(72, 24)
        Me.btnStartStop.TabIndex = 3
        Me.btnStartStop.Text = "Start"
        '
        'btnSnapImage
        '
        Me.btnSnapImage.Location = New System.Drawing.Point(336, 80)
        Me.btnSnapImage.Name = "btnSnapImage"
        Me.btnSnapImage.Size = New System.Drawing.Size(72, 24)
        Me.btnSnapImage.TabIndex = 4
        Me.btnSnapImage.Text = "Snap"
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.btnCodecProperties)
        Me.GroupBox1.Controls.Add(Me.cboCodecs)
        Me.GroupBox1.Location = New System.Drawing.Point(336, 120)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(152, 72)
        Me.GroupBox1.TabIndex = 5
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "AVI Codec"
        '
        'btnCodecProperties
        '
        Me.btnCodecProperties.Location = New System.Drawing.Point(8, 40)
        Me.btnCodecProperties.Name = "btnCodecProperties"
        Me.btnCodecProperties.Size = New System.Drawing.Size(72, 24)
        Me.btnCodecProperties.TabIndex = 1
        Me.btnCodecProperties.Text = "Properties"
        '
        'cboCodecs
        '
        Me.cboCodecs.Location = New System.Drawing.Point(8, 16)
        Me.cboCodecs.Name = "cboCodecs"
        Me.cboCodecs.Size = New System.Drawing.Size(136, 21)
        Me.cboCodecs.TabIndex = 0
        '
        'chkAVIPause
        '
        Me.chkAVIPause.Checked = True
        Me.chkAVIPause.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkAVIPause.Location = New System.Drawing.Point(416, 80)
        Me.chkAVIPause.Name = "chkAVIPause"
        Me.chkAVIPause.Size = New System.Drawing.Size(80, 24)
        Me.chkAVIPause.TabIndex = 6
        Me.chkAVIPause.Text = "AVI Pause"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(494, 268)
        Me.Controls.Add(Me.chkAVIPause)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.btnSnapImage)
        Me.Controls.Add(Me.btnStartStop)
        Me.Controls.Add(Me.btnSettings)
        Me.Controls.Add(Me.btnDevice)
        Me.Controls.Add(Me.IcImagingControl1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "Form1"
        Me.Text = "Image and AVI Capture"
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GroupBox1.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region


    ' Declaration of the snap image frame filter.
    '<<filterdeclaration
    Dim SnapImageFilter As TIS.Imaging.FrameFilter
    '>>
    Dim ImageCounter As Integer


    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        ImageCounter = 0
        With IcImagingControl1
            ' Resize the live video display to the size of the IC Imaging Control window
            .LiveDisplayDefault = False
            .LiveDisplayHeight = .Height
            .LiveDisplayWidth = .Width

            ' Try to load the previously used video capture device
            Try
                .LoadDeviceStateFromFile("device.xml", True)
            Catch ex As TIS.Imaging.ICException
                btnSettings.Enabled = False
                btnStartStop.Enabled = False
                ' If the loading fails, do nothing.
            End Try

            ' Try to load the "Save Image" filter. On success insert this filter in the device path.
            '<<loadfilter
            SnapImageFilter = IcImagingControl1.FrameFilterCreate("Save Image", "")
            If SnapImageFilter Is Nothing Then
                MessageBox.Show("Failed to load the Snap Image filter", "Filter Loading", MessageBoxButtons.OK, MessageBoxIcon.Warning)
            Else
                IcImagingControl1.DeviceFrameFilters.Add(SnapImageFilter)
            End If
            '>>
            ' Fill the combo box cboCodecs with the available codecs.
            cboCodecs.DataSource = .AviCompressors

            ' Select the first codec in the list and check whether it has a property dialog.
            cboCodecs.SelectedIndex = 0
            Dim Codec As TIS.Imaging.AviCompressor
            Codec = cboCodecs.SelectedItem
            If Not Codec Is Nothing Then
                If Codec.PropertyPageAvailable = True Then
                    btnCodecProperties.Enabled = True
                End If
            End If

        End With
    End Sub


    '
    ' If the device button has been clicked, the IC Imaging Control device 
    ' selection dialog will be shown.
    '
    Private Sub btnDevice_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnDevice.Click
        With IcImagingControl1
            ' Before the device selection dialog can be used, a probably running
            ' live video stram must be stopped.
            If .DeviceValid = True Then
                If .LiveVideoRunning = True Then
                    .LiveStop()
                End If
            End If

            .ShowDeviceSettingsDialog()

            ' If a valid video capture device has been selected then it will be
            ' saved to the file "device.xml".
            If .DeviceValid = True Then
                .SaveDeviceStateToFile("device.xml")
                btnSettings.Enabled = True
                btnStartStop.Enabled = True
            Else
                btnSettings.Enabled = False
                btnStartStop.Enabled = False
            End If
        End With
    End Sub


    '
    ' Show the property dialog to adjust the video capture device's properties
    '
    Private Sub btnSettings_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnSettings.Click
        With IcImagingControl1
            If .DeviceValid = True Then
                .ShowDeviceSettingsDialog()
                ' Save the new settings into the "device.xml" file.
                .SaveDeviceStateToFile("device.xml")
            End If
        End With
    End Sub

    '
    ' Start or stop the live video stream AVI capture. Per default the AVI capture
    ' is paused. 
    Private Sub btnStartStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStartStop.Click
        chkAVIPause.Checked = True
        With IcImagingControl1
            If .DeviceValid = True Then
                If .LiveVideoRunning = True Then
                    .AviStopCapture()
                    btnStartStop.Text = "Start"
                Else
                    .LiveCapturePause = chkAVIPause.CheckState
                    .AviStartCapture("test.avi", cboCodecs.SelectedItem)
                    btnStartStop.Text = "Stop"
                End If
            Else
                btnStartStop.Text = "Start"
                btnSettings.Enabled = False
                btnStartStop.Enabled = False
            End If
        End With
    End Sub

    ' Snap an image from the live video stream. This can only be done, if the live
    ' video is running and the SnapImageFilter is not nothing.
    ' The file name of the image will be advanced with a running number.
    '<<snapimage
    Private Sub btnSnapImage_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnSnapImage.Click
        With IcImagingControl1
            If .DeviceValid = True Then
                If .LiveVideoRunning = True Then
                    If Not SnapImageFilter Is Nothing Then
                        ImageCounter = ImageCounter + 1
                        Dim ImageFileName As String
                        ImageFileName = String.Format("Image{0}.jpg", ImageCounter)
                        SnapImageFilter.BeginParameterTransfer()
                        ' Passing the image name to the SnapImageFilter will snap the image
                        SnapImageFilter.SetStringParameter("ImageName", ImageFileName)
                        SnapImageFilter.EndParameterTransfer()
                    End If
                End If
            End If
        End With
    End Sub
    '>>

    '
    ' If the selection in the codec combo box changed, check whether the new
    ' selected codec has a property dialog.
    '
    Private Sub cboCodecs_SelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles cboCodecs.SelectedIndexChanged
        Dim Codec As TIS.Imaging.AviCompressor
        Codec = cboCodecs.SelectedItem
        If Not Codec Is Nothing Then
            btnCodecProperties.Enabled = Codec.PropertyPageAvailable
        End If
    End Sub

    '
    ' If the codec properties button has been clicked, show the property dialog
    ' of the selected codec.
    Private Sub btnCodecProperties_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCodecProperties.Click
        Dim Codec As TIS.Imaging.AviCompressor
        Codec = cboCodecs.SelectedItem
        If Not Codec Is Nothing Then
            If Codec.PropertyPageAvailable = True Then
                Codec.ShowPropertyPage()
            End If
        End If
    End Sub

    ' Enable or disable the AVI capture pause. Even if the AVI capture is paused,
    ' it is possible to snap images through the SnapImage frame filter.
    Private Sub chkAVIPause_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chkAVIPause.CheckedChanged
        IcImagingControl1.LiveCapturePause = chkAVIPause.CheckState
    End Sub
End Class
