#pragma once
// Port hooks into the fake server route (fakeapi.cpp), for the restore run's local server.
namespace soa::native::fakeapi {
// Queues the request of FakeApiCaller::<method> (e.g. "GetPlayMission") as if the game had called
// it; the fake server answers it on the next frame. False without SOA_FAKE_SERVER or for an
// unknown method.
bool queue_request(const char* method);
}  // namespace soa::native::fakeapi
