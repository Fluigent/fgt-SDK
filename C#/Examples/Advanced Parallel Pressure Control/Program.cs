using System;
using System.Threading;
using System.Threading.Tasks;
using fgt_sdk;

namespace Advanced_Parallel_Pressure_Control
{
    /// <summary>
    /// This example shows how to send concurrent pressure orders using threads.
    /// Dll handle parallel calls, functions can be called simultaneously. This demonstrate thread handling.
    ///
    /// Note that the same result is obtained using successive calls as all functions call is executed instantly(within few µs)
    ///
    /// Hardware setup: At least two Fluigent pressure controllers (MFCS, MFCS-EZ or FlowEZ)
    /// </summary>
    static class Program
    {
        static void Main(string[] args)
        {
            // Get total number , SN and type of detected Fluigent instrument controller
            var (controllersCount, instruments) = fgtSdk.Fgt_detect();
            Console.WriteLine($"Total number of controller(s): {controllersCount}");

            if (controllersCount > 0)
            {
                CancellationTokenSource _cts = new CancellationTokenSource();
                // Get total number of initialized pressure channel(s)
                var (errCode, pressureChannelsCount) = fgtSdk.Fgt_get_pressureChannelCount();
                Console.WriteLine($"Total number of pressure channels: {pressureChannelsCount}");

                // If there are enough instruments, launch tasks that generate pressure randomly on first two instruments
                if (pressureChannelsCount >= 2)
                {
                    var task1 = Task.Factory.StartNew(() => RandomPressureGeneration(0, TimeSpan.FromSeconds(2), _cts.Token));
                    var task2 = Task.Factory.StartNew(() => RandomPressureGeneration(1, TimeSpan.FromSeconds(5), _cts.Token));

                    Thread.Sleep(TimeSpan.FromSeconds(20));
                    _cts.Cancel();

                    Task.WhenAll(task1, task2);
                    Console.WriteLine("Both pressure generation tasks have completed their execution");
                }
                else
                {
                    Console.WriteLine("Please make sure that your hardware setup matches this example's requirements and that all instruments are connected to the computer");
                }
            }
            else
            {
                Console.WriteLine("Please make sure that your hardware setup matches this example's requirements and that all instruments are connected to the computer");
            }

            fgtSdk.Fgt_close();

            Console.WriteLine("Close this console by pressing enter");
            Console.ReadLine();
        }

        /// <summary>
        /// Randomly generate pressure
        /// </summary>
        /// <param name="pressureIndex">Pressure channel index to generate pressure on</param>
        /// <param name="period">Pressure generation refresh period</param>
        /// <param name="token">Cancellation token</param>
        private static Task RandomPressureGeneration(uint pressureIndex, TimeSpan period, CancellationToken token)
        {
            // Get pressure controller range
            var (errCode, pMin, pMax) = fgtSdk.Fgt_get_pressureRange(pressureIndex);

            var rand = new Random();

            var pressureOrder = 0f;
            while (!token.IsCancellationRequested)
            {
                // Detect if it's a pull pressure source
                if (pMax != 0)
                {
                    pressureOrder = rand.Next((int) pMax);
                }
                else
                {
                    pressureOrder = -rand.Next((int) Math.Abs(pMin));
                }
                
                fgtSdk.Fgt_set_pressure(pressureIndex, pressureOrder);
                Console.WriteLine($"New pressure order: {pressureOrder} mBar on pressure source {pressureIndex}");
                token.WaitHandle.WaitOne(period);
            }

            Console.WriteLine($"Pressure generation on channel {pressureIndex} has ended");

            return Task.CompletedTask;
        }

    }
}
