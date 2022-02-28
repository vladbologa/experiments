package main

import (
	"context"
	"log"
	"time"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"

	pb "grpc-test-go/vlad/grpc_test"
)

func main() {
	conn, err := grpc.Dial("[::1]:5001", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatal("Cannot connect to service admin.")
	}
	defer conn.Close()

	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	client := pb.NewPingClient(conn)
	_, err = client.Send(ctx, &pb.PingRequest{Name: "Golang client"})
	if err == nil {
		log.Println("Sent message!")
	} else {
		log.Println("Did not send message!")
	}
}
