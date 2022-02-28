use grpc_test::ping_client::PingClient;
use grpc_test::PingRequest;

pub mod grpc_test {
    tonic::include_proto!("grpc_test");
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut client = PingClient::connect("http://[::1]:5001").await?;

    let request = tonic::Request::new(PingRequest {
        name: "Rust client".into(),
    });

    let response = client.send(request).await?;
    println!("Response={:?}", response);

    Ok(())
}
