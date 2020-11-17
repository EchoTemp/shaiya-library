using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Internal;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Abstractions;
using Microsoft.Extensions.DependencyInjection;
using Newtonsoft.Json;
using Shaiya.Web.Api.Services;

namespace Shaiya.Web.Api
{
    /// <summary>
    /// Handles the configuration of the web server.
    /// </summary>
    public class Startup
    {
        /// <summary>
        /// Configures the services to use.
        /// </summary>
        /// <param name="services">The collection of services.</param>
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddMvcCore()
                .AddJsonFormatters(opts =>
                {
                    opts.TypeNameHandling = TypeNameHandling.None;
                });
            services.AddSingleton(provider => new GameService());
        }

        /// <summary>
        /// Configures the web server application
        /// </summary>
        /// <param name="app">The web app.</param>
        public void Configure(IApplicationBuilder app)
        {
            app.UseMvc(routes =>
            {
                routes.MapRoute(
                    name: "default",
                    template: "{controller=Players}/{action=Index}/{id?}");
            });
        }
    }
}
