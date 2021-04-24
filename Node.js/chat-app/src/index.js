const express = require("express")
const http = require("http")
const socketio = require("socket.io")
const path = require("path")
const Filter = require("bad-words")
const { generateMessage, generateLocationMessage } = require("./utils/messages")
const {
  addUser,
  removeUser,
  getUser,
  getUsersInRoom,
} = require("./utils/users")

const app = express()
const server = http.createServer(app)
const io = socketio(server)
const port = process.env.PORT || 3000

const publicDirectoryPath = path.join(__dirname, "../public")

app.use(express.static(publicDirectoryPath))

//server(emit)->client(receive)-countUpdated
//client(emit)->server(receive)-increment
//emit sends to particular connection
//broadcast sends to all except THE connection
io.on("connection", (socket) => {
  console.log("New WebSocket connection")

  //
  socket.on("join", (options, callback) => {
    const { error, user } = addUser({ id: socket.id, ...options })

    if (error) {
      return callback(error)
    }

    socket.join(user.room)
    socket.emit("message", generateMessage("Admin", "Welcome!"))
    socket.broadcast
      .to(user.room)
      .emit("message", generateMessage("Admin", `${user.username} has joined!`))

    io.to(user.room).emit("roomData", {
      room: user.room,
      users: getUsersInRoom(user.room),
    })
    //socket.emit, io.emit, socket.broadcast.emit
    //io.to.emit emits an event in specific room
    // socket.broadcast.to.emit send event to room to all users except specific client
    callback()
  })

  socket.on("sendMessage", (message, callback) => {
    const filter = new Filter()
    user = getUser(socket.id)

    if (filter.isProfane(message)) {
      return callback("Profanity is not allowed!")
    }

    io.to(user.room).emit("message", generateMessage(user.username, message))
    callback()
  })

  socket.on("sendLocation", (coords, callback) => {
    const user = getUser(socket.id)
    io.to(user.room).emit(
      "locationMessage",
      generateLocationMessage(
        user.username,
        `https://google.com/maps?q=${coords.latitude},${coords.longitude}`
      )
    )
    callback()
  })

  socket.on("disconnect", () => {
    const user = removeUser(socket.id)

    if (user) {
      io.to(user.room).emit(
        "message",
        generateMessage("Admin", `${user.username} has left!`)
      )
      io.to(user.room).emit("roomData", {
        room: user.room,
        users: getUsersInRoom(user.room),
      })
    }
  })
})

server.listen(port, () => {
  console.log(`Server is up on port ${port}.`)
})
