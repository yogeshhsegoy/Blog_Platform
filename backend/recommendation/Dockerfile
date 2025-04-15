# Step 1: Build the jar
FROM maven:3.9.5-eclipse-temurin-21 AS build
WORKDIR /app
COPY pom.xml .
COPY src ./src
RUN mvn clean package -DskipTests

# Step 2: Run the app
FROM eclipse-temurin:21-jre

# Install system dependencies
RUN apt-get update && apt-get install -y libgomp1 && rm -rf /var/lib/apt/lists/*

# Set up DJL cache directory
ENV DJL_CACHE_DIR=/app/.djl.ai
RUN mkdir -p /app/.djl.ai && chmod -R 777 /app/.djl.ai

# Copy the jar
COPY --from=build /app/target/*.jar app.jar

EXPOSE 8080
ENTRYPOINT ["java", "-Dorg.slf4j.simpleLogger.log.ai.djl=debug", "-jar", "/app.jar"]