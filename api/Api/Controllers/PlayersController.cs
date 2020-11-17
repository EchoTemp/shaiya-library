using Shaiya.Web.Api.Models;
using Shaiya.Web.Api.Services;
using System.Collections.Generic;
using System.Web.Mvc;

namespace Shaiya.Web.Api.Controllers
{
    /// <summary>
    /// Handles player related routes.
    /// </summary>
    [Route("[controller]")]
    public class PlayersController : Controller
    {
        /// <summary>
        /// The game service instance.
        /// </summary>
        private readonly GameService _service;

        /// <summary>
        /// Initialises this controller.
        /// </summary>
        /// <param name="service">The game service.</param>
        public PlayersController(GameService service)
        {
            _service = service;
        }

        /// <summary>
        /// The index returns a list of all online players.
        /// </summary>
        /// <returns>The online players.</returns>
        [HttpGet]
        public List<CUser> Index()
        {
            return _service.GetOnlineUsers();
        }
    }
}
