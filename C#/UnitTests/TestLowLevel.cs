using System;
using System.Collections.Generic;
using fgt_sdk;
using fgt_sdk.Enums;
using Xunit;

namespace UnitTests
{
    public class TestLowLevel: IDisposable
    {
        [Fact]
        public void InitWithoutInstrumentsReturnsRighterrCode()
        {
            var errCode = fgtSdk.Fgt_init();
            Assert.Equal(fgt_ERROR_CODE.No_instr_found, errCode);
        }

        [Fact]
        public void DetectWithoutInstrumentsReturnEmptyArray()
        {
            var (count, instruments) = fgtSdk.Fgt_detect();
            Assert.Equal(0, count);
            Assert.Empty(instruments);
        }

        [Fact]
        public void ControllersInfoStructIsFilledCorrectly()
        {
            var (errCode, info) = fgtSdk.Fgt_get_controllersInfo();
            // TODO find a way to verify that the method is working correctly
            Assert.Equal(fgt_ERROR_CODE.No_instr_found, errCode);
            Assert.Empty(info);
        }

        [Fact]
        public void PressureUnitChange()
        {
            var (errCode, count) = fgtSdk.Fgt_get_pressureChannelCount();
            Assert.Equal(fgt_ERROR_CODE.OK, errCode);

            if (count <= 0) return;

            const string kpa = "kPa";
            errCode = fgtSdk.Fgt_set_pressureUnit(0, kpa);
            Assert.Equal(fgt_ERROR_CODE.OK, errCode);

            string unit;
            (errCode, unit) = fgtSdk.Fgt_get_pressureUnit(0);
            Assert.Equal(fgt_ERROR_CODE.OK, errCode);
            Assert.Equal(kpa, unit);
        }

        [Fact]
        public void SetSessionPressureUnit()
        {
            var errCode = fgtSdk.Fgt_set_sessionPressureUnit("PSI");
            Assert.Equal(fgt_ERROR_CODE.No_instr_found, errCode);

            //errCode = LowLevel.Fgt_set_sessionPressureUnit("invalidunit");
            //Assert.Equal(fgt_ERROR_CODE.Wrong_parameter, errCode);
        }

        [Fact]
        public void PressureChannelsInfoIsFilledCorrectly()
        {
            var (errCode, info) = fgtSdk.Fgt_get_pressureChannelsInfo();
            Assert.Equal(fgt_ERROR_CODE.No_instr_found, errCode);
            Assert.Empty(info);
        }

        [Fact]
        public void TtlChannelsInfoIsFilledCorrectly()
        {
            var (errCode, info) = fgtSdk.Fgt_get_TtlChannelsInfo();
            Assert.Equal(fgt_ERROR_CODE.No_instr_found, errCode);
            Assert.Empty(info);
        }

        [Fact]
        public void SensorChannelsInfoIsFilledCorrectly()
        {
            //var (errCode, channelsInfo) = LowLevel.Fgt_get_sensorChannelsInfo();
            var (errCode, info) = fgtSdk.Fgt_get_sensorChannelsInfo();
            Assert.Equal(fgt_ERROR_CODE.No_instr_found, errCode);
            Assert.Empty(info);
        }


        [Fact]
        public void InitExWithoutInstrumentsReturnsRighterrCode()
        {
            var errCode = fgtSdk.Fgt_initEx(new List<ushort>(0));
            Assert.Equal(fgt_ERROR_CODE.No_instr_found, errCode);
        }

        [Fact]
        public void GetPressureChannelsCountWithoutInstruments()
        {
            var (errCode, count) = fgtSdk.Fgt_get_pressureChannelCount();
            Assert.Equal(fgt_ERROR_CODE.OK, errCode);
            Assert.Equal(0, count);
        }

        [Fact]
        public void GetSensorChannelsCountWithoutInstruments()
        {
            var (errCode, count) = fgtSdk.Fgt_get_sensorChannelCount();
            Assert.Equal(fgt_ERROR_CODE.OK, errCode);
            Assert.Equal(0, count);
        }

        [Fact]
        public void GetTtlChannelsCountWithoutInstruments()
        {
            var (errCode, count) = fgtSdk.Fgt_get_TtlChannelCount();
            Assert.Equal(fgt_ERROR_CODE.OK, errCode);
            Assert.Equal(0, count);
        }

        public void Dispose()
        {
            fgtSdk.Fgt_close();
        }
    }
}
