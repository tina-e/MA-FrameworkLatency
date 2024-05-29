#!/usr/bin/python3

# this program is based on tutorials by ZetCode
# https://zetcode.com/wxpython

import wx

class TestApp(wx.Frame):
    def __init__(self, *args, **kw):
        super(TestApp, self).__init__(*args, **kw)
        self.renderer = wx.GraphicsRenderer.GetDirect2DRenderer()

        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_LEFT_DOWN, self.OnClick)
        self.Bind(wx.EVT_LEFT_UP, self.OnRelease)

        self.color = '#000000'
        self.img = wx.Bitmap('noise.png')

        self.pressed = False
        self.SetTitle("framework")
        self.SetBackgroundColour(self.color)
        self.ShowFullScreen(True)

    def OnPaint(self, e):
        dc = wx.PaintDC(self)
        gc = self.renderer.CreateContext(dc)
        if self.pressed:
            gc.DrawBitmap(self.img, 0, 0, 1920, 1080) 


    def OnClick(self, e):
        self.pressed = True
        e.Skip()
        self.Refresh()

    def OnRelease(self, e):
        self.pressed = False
        e.Skip()
        self.Refresh()


app = wx.App()
test_app = TestApp(None)
test_app.Show()
app.MainLoop()

