use tonic::{transport::Server, Request, Response, Status};

use grpc_test::ping_server::{Ping, PingServer};
use grpc_test::{PingRequest, PingResponse};

pub mod grpc_test {
    tonic::include_proto!("grpc_test");
}

#[derive(Debug, Default)]
pub struct RustPingServer {}

#[tonic::async_trait]
impl Ping for RustPingServer {
    async fn send(&self, request: Request<PingRequest>) -> Result<Response<PingResponse>, Status> {
        println!("Got a request: {:?}", request);

        let reply = grpc_test::PingResponse {
            message: format!("Hello {}!", request.into_inner().name).into(),
        };

        Ok(Response::new(reply))
    }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let addr = "[::1]:5001".parse()?;
    let ping_server = RustPingServer::default();

    Server::builder()
        .add_service(PingServer::new(ping_server))
        .serve(addr)
        .await?;

    Ok(())
}
