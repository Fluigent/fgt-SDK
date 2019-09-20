<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="16008000">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Examples" Type="Folder">
			<Item Name="Advanced Custom Sensor Regulation.vi" Type="VI" URL="../Examples/Advanced Custom Sensor Regulation.vi"/>
			<Item Name="Advanced Features.vi" Type="VI" URL="../Examples/Advanced Features.vi"/>
			<Item Name="Advanced Parallel Pressure Control.vi" Type="VI" URL="../Examples/Advanced Parallel Pressure Control.vi"/>
			<Item Name="Advanced Specific Multiple Instruments.vi" Type="VI" URL="../Examples/Advanced Specific Multiple Instruments.vi"/>
			<Item Name="Basic Get Instruments Info.vi" Type="VI" URL="../Examples/Basic Get Instruments Info.vi"/>
			<Item Name="Basic Sensor Regulation.vi" Type="VI" URL="../Examples/Basic Sensor Regulation.vi"/>
			<Item Name="Basic Set Pressure.vi" Type="VI" URL="../Examples/Basic Set Pressure.vi"/>
		</Item>
		<Item Name="fgt_SDK.lvlib" Type="Library" URL="../fgt_SDK.lvlib"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="NI_PtbyPt.lvlib" Type="Library" URL="/&lt;vilib&gt;/ptbypt/NI_PtbyPt.lvlib"/>
			</Item>
			<Item Name="fgt_SDK_32.dll" Type="Document" URL="../../dlls/fgt_SDK_32.dll"/>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
