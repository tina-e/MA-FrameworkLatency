﻿#pragma checksum "D:\MA-FrameworkLatency\framework_tester_projects\framework_tester_no-fullscreen\WinUI3_deafult\MainWindow.xaml" "{8829d00f-11b8-4213-878b-770e8597ac16}" "33D0FAAC1163A652BF526925AB48B06D2AD878FA7420A85E5314646C2FEB8092"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace WinUI3_deafult
{
    partial class MainWindow : 
        global::Microsoft.UI.Xaml.Window, 
        global::Microsoft.UI.Xaml.Markup.IComponentConnector
    {

        /// <summary>
        /// Connect()
        /// </summary>
        [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.UI.Xaml.Markup.Compiler"," 3.0.0.2404")]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public void Connect(int connectionId, object target)
        {
            switch(connectionId)
            {
            case 2: // MainWindow.xaml line 11
                {
                    this.background = global::WinRT.CastExtensions.As<global::Microsoft.UI.Xaml.Controls.Canvas>(target);
                    ((global::Microsoft.UI.Xaml.Controls.Canvas)this.background).PointerPressed += this.onClick;
                    ((global::Microsoft.UI.Xaml.Controls.Canvas)this.background).PointerReleased += this.onRelease;
                }
                break;
            default:
                break;
            }
            this._contentLoaded = true;
        }

        /// <summary>
        /// GetBindingConnector(int connectionId, object target)
        /// </summary>
        [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.UI.Xaml.Markup.Compiler"," 3.0.0.2404")]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public global::Microsoft.UI.Xaml.Markup.IComponentConnector GetBindingConnector(int connectionId, object target)
        {
            global::Microsoft.UI.Xaml.Markup.IComponentConnector returnValue = null;
            return returnValue;
        }
    }
}

