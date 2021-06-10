# %%
import json
# 都先將 json 檔案 load 進來
with open('coaches.json') as f:
    coaches = json.load(f)
with open('players.json') as f:
    players = json.load(f)
with open('teams.json') as f:
    teams = json.load(f)

# %%
# q3
def extract_all_coaches(coaches):
    return coaches["league"]["standard"]
# q4
def extract_assitant_coaches(coaches):
    coaches_list = extract_all_coaches(coaches)
    ans = {}
    for c in coaches_list:
        if (c["isAssistant"]==True):# 找出每個 coach element 中 "isAssistant" 是 True 的就是 assistant coach
            team = c["teamSitesOnly"]["teamTricode"]
            if(team in ans):# 如果該隊已經出現在 dict 裡面，那就直接 append 在 list 裡面
                ans[team].append(c["firstName"]+" "+c["lastName"])
            else:# 如果該隊還沒有出現在 dict 裡面，那就創建一個 list
                ans[team] = []
                ans[team].append(c["firstName"]+" "+c["lastName"])
    return ans

# q5
class CoachAnalysis:
    def __init__(self, coaches):
        self.coaches = coaches
        
    def extract_head_coaches(self):
        coaches_list = extract_all_coaches(self.coaches)
        ans = {}
        for c in coaches_list:
            if (c["isAssistant"]==False):
                team = c["teamSitesOnly"]["teamTricode"]
                if(team in ans):
                    ans[team].append(c["firstName"]+" "+c["lastName"])
                else:
                    ans[team] = []
                    ans[team].append(c["firstName"]+" "+c["lastName"])
        return ans
    def extract_assitant_coaches(self):
        coaches_list = extract_all_coaches(self.coaches)
        ans = {}
        for c in coaches_list:
            if (c["isAssistant"]==True):
                team = c["teamSitesOnly"]["teamTricode"]
                if(team in ans):
                    ans[team].append(c["firstName"]+" "+c["lastName"])
                else:
                    ans[team] = []
                    ans[team].append(c["firstName"]+" "+c["lastName"])
        return ans
# print(extract_all_coaches(coaches)) # q3
# print(extract_assitant_coaches(coaches)) # q4

# c = CoachAnalysis(coaches) # q5
# print(c.extract_head_coaches()) # q5
# print(c.extract_assitant_coaches()) # q5

# %%
def cmp(d):# 用來在 sort 裡面比大小，sort 會依據這個 function 回傳的數值（體重）來執行排序演算法
    return d["weightKilograms"]
def get_sort_data(clean_p, reverse):
    clean_p.sort(key=cmp, reverse=reverse) # reverse=True 表示大到小，反之小到大
    weight = clean_p[0]["weightKilograms"]
    p = clean_p[0]["firstName"] + " " + clean_p[0]["lastName"]
    return {"weightKilograms":weight, "players":[p]}

# q6
def find_heaviest_lightest_players(players):
    clean_p = []
    for p in players['league']['standard']:
        if(p["weightKilograms"] != ""):# 先清掉 weightKilograms 為空的 element，不將這些 weightKilograms 做計算
            p["weightKilograms"] = float(p["weightKilograms"])
            clean_p.append(p)

    lightest = get_sort_data(clean_p, False)
    heaviest = get_sort_data(clean_p, True)
    return {"lightest":lightest, "heaviest": heaviest}
# print(find_heaviest_lightest_players(players)) # q6

# %%
def get_team_id(teams, name):
    for t in teams['league']['standard']:
        if(t["fullName"] == name):# 用 team 的名字 (fullName) 找出 teamId
            return t["teamId"]
# q7
def find_nuggets_sixers_players(players, teams):
    # 先得到兩隊的 teamId
    nuggets = get_team_id(teams, "Denver Nuggets")
    sixers = get_team_id(teams, "Philadelphia 76ers")
    nuggets_list = []
    sixers_list = []
    for p in players['league']['standard']:
        # 如果 player 的 teamId 符合，則將該 player 加入
        if(p["teamId"] == nuggets):
            nuggets_list.append(p["firstName"] + " " + p["lastName"])
        elif(p["teamId"] == sixers):
            sixers_list.append(p["firstName"] + " " + p["lastName"])
    ans = {"Denver Nuggets": nuggets_list, "Philadelphia 76ers": sixers_list}
    return ans

# print(find_nuggets_sixers_players(players, teams)) # q7

# %%
# q8
def find_lakers_coaches_players(coaches, players, teams):
    ans = {"headCoach":"", "assistantCoaches":[], "players":[]}
    # 先找出 lakers 的 teamId
    lakers = get_team_id(teams, 'Los Angeles Lakers')
    for c in coaches['league']['standard']:
        if(c["teamId"] == lakers and c["isAssistant"]==True): # assistant coach
            ans["assistantCoaches"].append(c["firstName"] + " " + c["lastName"])
        elif(c["teamId"] == lakers and c["isAssistant"]==False):# head coach
            ans["headCoach"] = c["firstName"] + " " + c["lastName"]
    for p in players['league']['standard']:
        if(p["teamId"] == lakers):
            ans["players"].append(p["firstName"] + " " + p["lastName"])
    return ans
    
# print(find_lakers_coaches_players(coaches, players, teams)) # q8


# %%
# q9
def find_teams_with_special_tricodes(teams):
    ans = {"not_tri":[]}
    for t in teams['league']['standard']:
        tmp_team_name = t["fullName"].replace(" ", "") # 將空白移除掉，像是 LA Clippers 的 tricode 是 LAC，也必須算入，所以需要將中間空白移除'
        if(tmp_team_name[0:3].lower() != t["tricode"].lower()):
            ans["not_tri"].append(t["fullName"])
    return ans
# print(find_teams_with_special_tricodes(teams)) # q9

