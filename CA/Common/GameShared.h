#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "WinSock2.h"
#include "Windows.h"
#include "Ws2tcpip.h"
typedef int socklen_t;
//typedef char* receiveBufer_t;


#include "memory"

#include "vector"
#include "unordered_map"
#include "string"
#include "list"
#include "queue"
#include "deque"
#include "unordered_set"
#include "cassert"

using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::queue;
using std::list;
using std::deque;
using std::unordered_map;
using std::string;
using std::unordered_set;

class Player;
class GameObject;

#include "ServerMath.h"

#include "StringUtils.h"
#include "SocketAddress.h"
#include "SocketAddressFactory.h"
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "SocketUtil.h"

#include "ByteSwap.h"
#include "LinkingContext.h"
#include "MemoryStream.h"
#include "MemoryBitStream.h"

#include "TransmissionData.h"
#include "InFlightPacket.h"
#include "AckRange.h"
#include "DeliveryNotificationManager.h"

#include "InputAction.h"
#include "InputState.h"
#include "Move.h"
#include "MoveList.h"


#include "GameObject.h"
#include "GameObjectRegistry.h"
#include "Player.h"
#include "World.h"
#include "Timing.h"

#include "Block.h"
#include "Bomb.h"
#include "Boom.h"


#include "StringUtils.h"
#include "ScoreBoardManager.h"

#include "WeightedTimedMovingAverage.h"
#include "ReplicationCommand.h"
#include "NetworkManager.h"
#include "Engine.h"
