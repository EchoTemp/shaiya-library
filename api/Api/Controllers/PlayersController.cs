using Microsoft.AspNetCore.Mvc;
using Shaiya.Web.Api.Models;
using Shaiya.Web.Api.Models.Http;
using Shaiya.Web.Api.Services;
using System.Collections.Generic;

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

        /// <summary>
        /// Teleports a player by name
        /// </summary>
        /// <returns>The response message</returns>
        [HttpPost]
        [Route("teleport")]
        public Response Teleport([FromBody] TeleportUserRequest request)
        {
            _service.TeleportUserByName(request.Name, request.Map, request.X, request.Z);
            return new Response { Message = "Success" };
        }
    }
}
