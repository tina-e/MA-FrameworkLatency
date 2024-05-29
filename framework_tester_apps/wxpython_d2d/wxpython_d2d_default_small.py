#!/usr/bin/python3

# this program is based on tutorials by ZetCode
# https://zetcode.com/wxpython

import wx
import time
import sys
import signal
import pandas

WIDTH = 100
HEIGHT = 100

class TestApp(wx.Frame):
    def __init__(self, parent, title, size, position, style):
        super(TestApp, self).__init__(parent, title=title, size=size, pos=position, style=style)
        self.renderer = wx.GraphicsRenderer.GetDirect2DRenderer()
        
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_LEFT_DOWN, self.OnClick)
        self.Bind(wx.EVT_LEFT_UP, self.OnRelease)

        self.color = '#000000'
        self.brush = wx.Brush(self.color)
        self.SetBackgroundColour(self.color)
        self.SetTitle("framework")
        self.Show()


    def OnPaint(self, e):
        dc = wx.PaintDC(self)
        gc = self.renderer.CreateContext(dc)
        # renderer = gc.GetRenderer()
        # print(renderer)
        # print(renderer.GetName())

        gc.SetBrush(self.brush)
        gc.SetPen(wx.TRANSPARENT_PEN)
        gc.DrawRectangle(0, 0, WIDTH, HEIGHT)

    def OnClick(self, e):
        self.color = '#FFFFFF'
        self.brush = wx.Brush(self.color)
        e.Skip()
        self.Refresh()

    def OnRelease(self, e):
        self.color = '#000000'
        self.brush = wx.Brush(self.color)
        e.Skip()
        self.Refresh()


def signal_handler(signal, frame):
    #print("signal wx")
    #df = pandas.DataFrame(data={"wxpython": click_timestamps})
    #df.to_csv("../../data/clicks/wxpython.csv", sep=',',index=False)
    sys.exit(0)

def main():
    app = wx.App()
    size = (WIDTH, HEIGHT)
    position = (0, 0)
    style = wx.NO_BORDER
    test_app = TestApp(None, title="framework", size=size, position=position, style=style)
    signal.signal(signal.SIGTERM, signal_handler)
    signal.signal(signal.SIGINT, signal_handler)
    app.MainLoop()


if __name__ == '__main__':
    main()
    