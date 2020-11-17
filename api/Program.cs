using Microsoft.AspNetCore;
using Microsoft.AspNetCore.Hosting;
using Shaiya.Web.Api;
using System.Threading.Tasks;

namespace Shaiya.Web
{
    /// <summary>
    /// The entry point for the Shaiya Web API.
    /// </summary>
    class Program
    {
        /// <summary>
        /// Initialise the web api.
        /// </summary>
        static async Task Main()
        {
            IWebHost host = WebHost.CreateDefaultBuilder()
                .UseStartup<Startup>()
                .Build();
            await host.RunAsync();
        }
    }
}
