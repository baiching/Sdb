#include <catch2/catch_test_macros.hpp>
#include <cstdio>
#include <string>

std::vector<std::string> run_sdb_test(const std::vector<std::string> &commands) {
  std::vector<std::string> output;

  FILE* pipe = popen("./Sdb", "r++");
  if (!pipe) {
    throw std::runtime_error("failed to open database process\n");
  }

  for (const auto &command: commands) {
    fprintf(pipe, "%s\n", command.c_str());
    fflush(pipe);
  }

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    std::string line = buffer;
    if (!line.empty() && line.back() == '\n') {
      line.pop_back();
    }

    output.push_back(line);
  }

  //close file
  pclose(pipe);

  return output;
}

TEST_CASE("database operations") {
  SECTION("inserts and retrives a row") {
    std::vector<std::string> commands = {
      "insert 1 user1 person1@bar.me",
      "select",
      ".exit"
    };

    auto result = run_sdb_test(commands);

    //Expected output
    std::vector<std::string> expected = {
      "sdb > Executed.",
      "sdb > (1, user1, person1@bar.com)",
      "Executed.",
      "sdb > "
    };

    REQUIRE(result.size() == 4);
    REQUIRE(result[0] == "db > Executed.");
    REQUIRE(result[1] == "db > (1, user1, person1@bar.com)");
    REQUIRE(result[2] == "Executed.");
    REQUIRE(result[3] == "db > ");
  }
}