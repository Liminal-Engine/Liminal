/**
 * @file liminal_json_io.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-04
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_TESTS_LIMINAL_JSON_IO_TEST_HPP_
#define LIMINAL_TESTS_LIMINAL_JSON_IO_TEST_HPP_

#include <string>

namespace liminal_json_io_test {
    const std::string SIMPLE_JSON_NO_ERROR =  R"(
{
    "name": "John Doe",
    "age": 30,
    "isEmployed": true,
    "address": {
        "story": {
            "left": 15,
            "right": 678.5
        },
        "street": "123 Main St",
        "city": "Anytown",
        "state": "Anystate",
        "postalCode": 12345,
        "anotherData": 42.84
    },
    "hobbies": [
        "reading",
        "gaming",
        "hiking",
        {
            "nestedHobby": "no"
        },
        {
            "secondNestedHobbies": ["un", "dos", 3, null],
            "nothingImportantHere": null
        }
    ],
    "happy": "yes"
}
)";
    const std::string LARGE_JSON_NO_ERROR = R"(
[
    {
      "_id": "658dacab33d37639bcd138b2",
      "index": 0,
      "guid": "018a1a54-0e66-44b2-bf88-6349a4839645",
      "isActive": false,
      "balance": "$2,399.08",
      "picture": "http://placehold.it/32x32",
      "age": 23,
      "eyeColor": "brown",
      "name": "Kirby Nielsen",
      "gender": "male",
      "company": "DRAGBOT",
      "email": "kirbynielsen@dragbot.com",
      "phone": "+1 (906) 540-3410",
      "address": "428 Franklin Avenue, Whitewater, Tennessee, 2242",
      "about": "Esse do exercitation adipisicing quis non culpa voluptate ea velit ipsum. Enim irure Lorem pariatur dolor quis mollit sunt elit. Aute magna mollit tempor nostrud ut ea eiusmod dolor ullamco non aliqua qui occaecat commodo.\r\n",
      "registered": "2019-12-25T04:23:12 -01:00",
      "latitude": -48.602054,
      "longitude": -110.70296,
      "tags": [
        "tempor",
        "proident",
        "ut",
        "sint",
        "ad",
        "laboris",
        "ullamco"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Young Weaver"
        },
        {
          "id": 1,
          "name": "David Dunlap"
        },
        {
          "id": 2,
          "name": "Shelley Benton"
        }
      ],
      "greeting": "Hello, Kirby Nielsen! You have 8 unread messages.",
      "favoriteFruit": "banana"
    },
    {
      "_id": "658dacaba46d4f5622abf29b",
      "index": 1,
      "guid": "d791b95a-9af5-4660-be81-d78bebc53968",
      "isActive": false,
      "balance": "$3,508.02",
      "picture": "http://placehold.it/32x32",
      "age": 24,
      "eyeColor": "brown",
      "name": "Concetta Richmond",
      "gender": "female",
      "company": "GEOFARM",
      "email": "concettarichmond@geofarm.com",
      "phone": "+1 (805) 469-2978",
      "address": "510 Poly Place, Wedgewood, Illinois, 3529",
      "about": "Minim cupidatat dolor mollit proident enim qui dolore dolor id nisi. Id sunt excepteur nisi officia elit qui aliqua excepteur aliquip fugiat et do Lorem. Qui cupidatat commodo consectetur do laborum elit aute ipsum aliquip. Pariatur dolore commodo enim aute excepteur.\r\n",
      "registered": "2014-05-14T02:37:16 -02:00",
      "latitude": -1.679872,
      "longitude": 41.222698,
      "tags": [
        "labore",
        "enim",
        "ipsum",
        "Lorem",
        "exercitation",
        "nulla",
        "est"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Wanda Erickson"
        },
        {
          "id": 1,
          "name": "Hillary Hines"
        },
        {
          "id": 2,
          "name": "Ella Curry"
        }
      ],
      "greeting": "Hello, Concetta Richmond! You have 6 unread messages.",
      "favoriteFruit": "strawberry"
    },
    {
      "_id": "658dacab8c421ce591f556cc",
      "index": 2,
      "guid": "c59f2000-29ab-47f9-99fb-81b74ca54f4e",
      "isActive": false,
      "balance": "$3,306.99",
      "picture": "http://placehold.it/32x32",
      "age": 31,
      "eyeColor": "brown",
      "name": "Nanette Reilly",
      "gender": "female",
      "company": "LUMBREX",
      "email": "nanettereilly@lumbrex.com",
      "phone": "+1 (849) 462-3868",
      "address": "440 Seaview Court, Bridgetown, Texas, 4718",
      "about": "Proident consequat anim do anim. Ea eu irure minim do exercitation mollit sunt proident nostrud. Sit dolore ea fugiat in labore laborum duis qui irure aliquip. Sunt officia exercitation veniam esse do officia veniam irure.\r\n",
      "registered": "2020-11-04T03:50:13 -01:00",
      "latitude": 85.768014,
      "longitude": -155.402524,
      "tags": [
        "velit",
        "culpa",
        "ullamco",
        "dolore",
        "id",
        "irure",
        "qui"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Hoffman Walsh"
        },
        {
          "id": 1,
          "name": "Rena Wheeler"
        },
        {
          "id": 2,
          "name": "Maxine Michael"
        }
      ],
      "greeting": "Hello, Nanette Reilly! You have 7 unread messages.",
      "favoriteFruit": "strawberry"
    },
    {
      "_id": "658dacab8d7d3ced74a05aa1",
      "index": 3,
      "guid": "17834ca4-52c3-4baa-a805-b7346b9f6233",
      "isActive": false,
      "balance": "$3,299.92",
      "picture": "http://placehold.it/32x32",
      "age": 35,
      "eyeColor": "blue",
      "name": "Carey Gibbs",
      "gender": "female",
      "company": "EURON",
      "email": "careygibbs@euron.com",
      "phone": "+1 (882) 428-2161",
      "address": "490 Hewes Street, Carrsville, Alabama, 1582",
      "about": "Ut nulla proident occaecat laboris minim sit. Nulla labore dolor sint sunt sit dolore enim officia magna ullamco est labore ea. Dolor nisi cillum eu in. Lorem esse duis occaecat velit sint.\r\n",
      "registered": "2016-11-17T07:20:56 -01:00",
      "latitude": 10.694015,
      "longitude": -23.726349,
      "tags": [
        "commodo",
        "minim",
        "ut",
        "exercitation",
        "magna",
        "elit",
        "ipsum"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Santiago Guzman"
        },
        {
          "id": 1,
          "name": "Suzanne Baird"
        },
        {
          "id": 2,
          "name": "Mcintosh Dodson"
        }
      ],
      "greeting": "Hello, Carey Gibbs! You have 8 unread messages.",
      "favoriteFruit": "apple"
    },
    {
      "_id": "658dacab7eaa8f2d603e8b2a",
      "index": 4,
      "guid": "09b3d289-0f08-47bd-b0bc-1bf090c18c67",
      "isActive": true,
      "balance": "$2,455.57",
      "picture": "http://placehold.it/32x32",
      "age": 22,
      "eyeColor": "brown",
      "name": "Foster Rush",
      "gender": "male",
      "company": "FUTURITY",
      "email": "fosterrush@futurity.com",
      "phone": "+1 (877) 481-3954",
      "address": "842 Dover Street, Noblestown, Arizona, 1535",
      "about": "Sunt minim consequat pariatur cupidatat sunt elit. Excepteur commodo elit eiusmod incididunt ullamco ullamco. Labore magna fugiat veniam voluptate minim eu laboris laborum eiusmod esse nulla aute ullamco. Ut nisi reprehenderit adipisicing mollit esse voluptate proident officia adipisicing est fugiat dolor exercitation. Dolor elit cupidatat ullamco duis eiusmod est eiusmod cillum laborum ex sit. Excepteur tempor id commodo do ad mollit fugiat velit amet exercitation adipisicing Lorem irure. Irure officia nostrud commodo labore.\r\n",
      "registered": "2018-04-10T01:53:57 -02:00",
      "latitude": 87.928805,
      "longitude": 49.699276,
      "tags": [
        "sint",
        "consectetur",
        "occaecat",
        "pariatur",
        "Lorem",
        "velit",
        "occaecat"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Shauna Gamble"
        },
        {
          "id": 1,
          "name": "Hurst Brock"
        },
        {
          "id": 2,
          "name": "Kerri Whitfield"
        }
      ],
      "greeting": "Hello, Foster Rush! You have 8 unread messages.",
      "favoriteFruit": "apple"
    },
    {
      "_id": "658dacabbdeab926f58c049d",
      "index": 5,
      "guid": "3daf64bf-e3ab-49ba-9f53-5aa54295dd38",
      "isActive": false,
      "balance": "$3,048.53",
      "picture": "http://placehold.it/32x32",
      "age": 40,
      "eyeColor": "brown",
      "name": "Horne Carver",
      "gender": "male",
      "company": "GEEKKO",
      "email": "hornecarver@geekko.com",
      "phone": "+1 (840) 516-3312",
      "address": "773 Dekoven Court, Coldiron, District Of Columbia, 8604",
      "about": "Occaecat sunt esse nostrud proident esse anim excepteur. Est amet qui id qui excepteur nulla dolore exercitation. Sit mollit et exercitation dolore ipsum sunt excepteur incididunt incididunt eiusmod tempor. Mollit consectetur deserunt aute voluptate labore qui consectetur ut amet ut mollit. Commodo sit aute et pariatur occaecat sint velit deserunt nulla. Laboris qui minim velit qui elit enim ipsum ullamco do.\r\n",
      "registered": "2014-07-29T07:28:45 -02:00",
      "latitude": -81.707036,
      "longitude": 26.073499,
      "tags": [
        "nostrud",
        "laborum",
        "sint",
        "aliquip",
        "Lorem",
        "nostrud",
        "dolor"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Jenifer Parrish"
        },
        {
          "id": 1,
          "name": "Mariana Mcintosh"
        },
        {
          "id": 2,
          "name": "Opal Mayer"
        }
      ],
      "greeting": "Hello, Horne Carver! You have 3 unread messages.",
      "favoriteFruit": "banana"
    },
    {
      "_id": "658dacab5f73683de5800404",
      "index": 6,
      "guid": "82c53429-6215-471f-ad22-75ea1c7e4106",
      "isActive": false,
      "balance": "$2,846.09",
      "picture": "http://placehold.it/32x32",
      "age": 35,
      "eyeColor": "brown",
      "name": "Johnnie Lamb",
      "gender": "female",
      "company": "CANDECOR",
      "email": "johnnielamb@candecor.com",
      "phone": "+1 (877) 444-2636",
      "address": "280 Surf Avenue, Basye, West Virginia, 5224",
      "about": "Elit amet fugiat voluptate aliqua qui anim anim magna adipisicing elit pariatur. Esse aliquip eiusmod fugiat et qui ad cillum aute cupidatat sunt. Qui cillum proident elit sunt labore in ex voluptate et veniam laboris commodo. Commodo aliqua id qui proident non ipsum Lorem do voluptate qui eiusmod ad ullamco.\r\n",
      "registered": "2015-06-03T03:31:50 -02:00",
      "latitude": 7.731949,
      "longitude": 4.52301,
      "tags": [
        "ullamco",
        "dolore",
        "officia",
        "sit",
        "deserunt",
        "exercitation",
        "deserunt"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Ramirez Garrison"
        },
        {
          "id": 1,
          "name": "Potts Reeves"
        },
        {
          "id": 2,
          "name": "Marcie Vincent"
        }
      ],
      "greeting": "Hello, Johnnie Lamb! You have 2 unread messages.",
      "favoriteFruit": "banana"
    },
    {
      "_id": "658dacab3e0fe5e3faeadb2d",
      "index": 7,
      "guid": "55cd734e-ddc1-4a5f-ab0d-3bd742874c91",
      "isActive": true,
      "balance": "$2,907.31",
      "picture": "http://placehold.it/32x32",
      "age": 40,
      "eyeColor": "blue",
      "name": "Irwin Mccormick",
      "gender": "male",
      "company": "ENOMEN",
      "email": "irwinmccormick@enomen.com",
      "phone": "+1 (891) 503-3722",
      "address": "890 Matthews Place, Grandview, Wyoming, 408",
      "about": "Elit cupidatat enim ex velit ad sint esse esse exercitation. Fugiat officia commodo duis cupidatat. Laboris qui culpa sit excepteur eu officia velit elit. Voluptate eiusmod aliqua elit eiusmod cupidatat esse consequat dolore occaecat nostrud adipisicing. Incididunt labore Lorem excepteur dolore do aliquip dolore id ut. Ipsum ex mollit aliquip occaecat nisi amet duis et cillum ad id. Do nisi commodo ad in id consequat anim proident et.\r\n",
      "registered": "2016-03-28T11:37:28 -02:00",
      "latitude": -74.848542,
      "longitude": -37.587732,
      "tags": [
        "labore",
        "proident",
        "ut",
        "et",
        "pariatur",
        "veniam",
        "non"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Dotson Boyd"
        },
        {
          "id": 1,
          "name": "Sheila Coffey"
        },
        {
          "id": 2,
          "name": "Kinney Anthony"
        }
      ],
      "greeting": "Hello, Irwin Mccormick! You have 1 unread messages.",
      "favoriteFruit": "apple"
    },
    {
      "_id": "658dacabe558dc5bbd34bc9b",
      "index": 8,
      "guid": "426cd5ef-0289-4f21-9220-cf2d07ac1327",
      "isActive": true,
      "balance": "$3,391.87",
      "picture": "http://placehold.it/32x32",
      "age": 28,
      "eyeColor": "blue",
      "name": "Blair Key",
      "gender": "male",
      "company": "CORMORAN",
      "email": "blairkey@cormoran.com",
      "phone": "+1 (933) 448-2680",
      "address": "701 Sunnyside Court, Ruckersville, Oklahoma, 1910",
      "about": "Incididunt sunt exercitation dolor veniam. Deserunt reprehenderit consectetur ut deserunt officia sunt veniam anim. Elit consectetur incididunt deserunt incididunt ad cillum. Quis reprehenderit ad ut sint est deserunt ea magna ex. Commodo ex ea incididunt sunt ullamco pariatur pariatur elit ut deserunt. Aute Lorem amet elit amet nisi. Adipisicing ullamco eiusmod culpa consequat cupidatat consectetur fugiat aliqua aliquip consequat aute ex ipsum.\r\n",
      "registered": "2019-01-14T08:43:28 -01:00",
      "latitude": -4.603895,
      "longitude": -15.716437,
      "tags": [
        "velit",
        "velit",
        "fugiat",
        "aute",
        "laborum",
        "in",
        "qui"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Pamela Cantu"
        },
        {
          "id": 1,
          "name": "Lupe Hodges"
        },
        {
          "id": 2,
          "name": "Maureen Atkinson"
        }
      ],
      "greeting": "Hello, Blair Key! You have 3 unread messages.",
      "favoriteFruit": "banana"
    },
    {
      "_id": "658dacaba8261c8529b18b64",
      "index": 9,
      "guid": "7e9e9b77-8027-4ac2-a227-6f9ed516908d",
      "isActive": true,
      "balance": "$3,718.76",
      "picture": "http://placehold.it/32x32",
      "age": 39,
      "eyeColor": "brown",
      "name": "Paul Gomez",
      "gender": "male",
      "company": "HOPELI",
      "email": "paulgomez@hopeli.com",
      "phone": "+1 (843) 558-3284",
      "address": "620 Lott Avenue, Indio, Palau, 4835",
      "about": "In cillum aliquip culpa laboris irure. Cupidatat Lorem laborum sint sint culpa consectetur laborum irure officia pariatur ex velit id pariatur. Laboris reprehenderit excepteur qui adipisicing excepteur. Culpa ipsum elit aute qui aliquip voluptate ut ex id veniam deserunt occaecat enim. Ea commodo labore sint deserunt consectetur commodo aliqua. Aliqua aute velit laboris nisi voluptate et nisi do dolor in labore laboris dolore.\r\n",
      "registered": "2017-10-03T10:16:17 -02:00",
      "latitude": 75.092396,
      "longitude": 85.170864,
      "tags": [
        "voluptate",
        "do",
        "incididunt",
        "commodo",
        "ea",
        "in",
        "labore"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Gomez Rowe"
        },
        {
          "id": 1,
          "name": "Kasey Mason"
        },
        {
          "id": 2,
          "name": "Jan Wynn"
        }
      ],
      "greeting": "Hello, Paul Gomez! You have 8 unread messages.",
      "favoriteFruit": "banana"
    },
    {
      "_id": "658dacabf4a1601190d10f45",
      "index": 10,
      "guid": "5e04ad66-fb4b-4f81-b177-033270c2b463",
      "isActive": false,
      "balance": "$2,375.44",
      "picture": "http://placehold.it/32x32",
      "age": 25,
      "eyeColor": "blue",
      "name": "Bridgette Dudley",
      "gender": "female",
      "company": "COMSTRUCT",
      "email": "bridgettedudley@comstruct.com",
      "phone": "+1 (935) 492-3513",
      "address": "735 Clinton Avenue, Balm, Ohio, 4115",
      "about": "Velit excepteur voluptate cupidatat veniam cillum laborum ad ad. Enim sunt do in irure dolor tempor exercitation eu fugiat incididunt commodo. Eiusmod cupidatat adipisicing voluptate reprehenderit ut irure labore Lorem mollit Lorem officia mollit. Excepteur ad ea in excepteur irure occaecat sunt Lorem ea voluptate cupidatat laboris. Officia aliqua mollit laborum aliqua laborum tempor minim nisi ad anim voluptate nulla duis.\r\n",
      "registered": "2018-08-21T02:05:35 -02:00",
      "latitude": -15.612261,
      "longitude": -15.377555,
      "tags": [
        "velit",
        "in",
        "deserunt",
        "sit",
        "est",
        "in",
        "culpa"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Bernadine Mueller"
        },
        {
          "id": 1,
          "name": "Harrison Solomon"
        },
        {
          "id": 2,
          "name": "Marshall Stevenson"
        }
      ],
      "greeting": "Hello, Bridgette Dudley! You have 3 unread messages.",
      "favoriteFruit": "banana"
    },
    {
      "_id": "658dacabd77be758b76c9603",
      "index": 11,
      "guid": "0a95bb17-4fd1-42be-8032-8a6121186dcd",
      "isActive": true,
      "balance": "$2,950.04",
      "picture": "http://placehold.it/32x32",
      "age": 36,
      "eyeColor": "green",
      "name": "Rose Fischer",
      "gender": "female",
      "company": "ANIMALIA",
      "email": "rosefischer@animalia.com",
      "phone": "+1 (968) 575-3554",
      "address": "397 Macon Street, Leola, Montana, 2278",
      "about": "Nulla voluptate laborum sunt pariatur nostrud est nostrud ipsum. Laborum velit nostrud nulla non aute laboris laboris est. Cupidatat occaecat Lorem tempor voluptate.\r\n",
      "registered": "2015-11-06T03:26:07 -01:00",
      "latitude": -30.090212,
      "longitude": -145.625314,
      "tags": [
        "ea",
        "ex",
        "ex",
        "nisi",
        "reprehenderit",
        "eu",
        "anim"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Vicky Pierce"
        },
        {
          "id": 1,
          "name": "Katie Vaughn"
        },
        {
          "id": 2,
          "name": "Elvia Gillespie"
        }
      ],
      "greeting": "Hello, Rose Fischer! You have 8 unread messages.",
      "favoriteFruit": "strawberry"
    },
    {
      "_id": "658dacabec6d734459019b64",
      "index": 12,
      "guid": "d55a789f-4eb3-47cd-9535-1e3e3b7e395b",
      "isActive": true,
      "balance": "$2,582.68",
      "picture": "http://placehold.it/32x32",
      "age": 26,
      "eyeColor": "blue",
      "name": "Ball Collins",
      "gender": "male",
      "company": "AQUASSEUR",
      "email": "ballcollins@aquasseur.com",
      "phone": "+1 (993) 407-2490",
      "address": "968 Charles Place, Stagecoach, Pennsylvania, 1933",
      "about": "Laboris pariatur ullamco dolore duis adipisicing id consequat ea magna. Eiusmod cillum et eu magna. Ut veniam labore dolore dolore mollit amet anim amet deserunt ex. Occaecat qui ex dolor ipsum tempor nisi amet officia cupidatat minim commodo. Adipisicing consectetur enim sit reprehenderit nisi.\r\n",
      "registered": "2019-01-24T09:20:41 -01:00",
      "latitude": -65.413216,
      "longitude": 66.507941,
      "tags": [
        "exercitation",
        "id",
        "adipisicing",
        "veniam",
        "Lorem",
        "elit",
        "enim"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Kirsten Mcmahon"
        },
        {
          "id": 1,
          "name": "Deann Schwartz"
        },
        {
          "id": 2,
          "name": "Fitzgerald Cobb"
        }
      ],
      "greeting": "Hello, Ball Collins! You have 4 unread messages.",
      "favoriteFruit": "apple"
    },
    {
      "_id": "658dacab9b273aca479985f8",
      "index": 13,
      "guid": "072ed25a-fd88-416c-9363-d951d05ae08f",
      "isActive": false,
      "balance": "$1,493.17",
      "picture": "http://placehold.it/32x32",
      "age": 29,
      "eyeColor": "brown",
      "name": "Whitney Hooper",
      "gender": "male",
      "company": "QIAO",
      "email": "whitneyhooper@qiao.com",
      "phone": "+1 (953) 514-2469",
      "address": "512 Ovington Avenue, Wauhillau, Nevada, 1842",
      "about": "Cillum sint sit id ullamco officia et excepteur mollit eu pariatur sint labore. Id consequat est mollit eu adipisicing sunt qui proident cupidatat nisi. Elit exercitation commodo adipisicing commodo.\r\n",
      "registered": "2022-03-08T09:55:37 -01:00",
      "latitude": -45.330623,
      "longitude": -38.28212,
      "tags": [
        "incididunt",
        "culpa",
        "dolor",
        "aute",
        "ex",
        "cupidatat",
        "officia"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Nola Stanton"
        },
        {
          "id": 1,
          "name": "Noble Powers"
        },
        {
          "id": 2,
          "name": "Myers Malone"
        }
      ],
      "greeting": "Hello, Whitney Hooper! You have 8 unread messages.",
      "favoriteFruit": "apple"
    },
    {
      "_id": "658dacab590a88279c1c18ed",
      "index": 14,
      "guid": "e01a13ae-554e-4df8-b6d1-2dddbd337ecd",
      "isActive": false,
      "balance": "$3,025.09",
      "picture": "http://placehold.it/32x32",
      "age": 31,
      "eyeColor": "brown",
      "name": "Madelyn Gilliam",
      "gender": "female",
      "company": "SYNTAC",
      "email": "madelyngilliam@syntac.com",
      "phone": "+1 (868) 495-2077",
      "address": "270 Celeste Court, Thermal, Indiana, 259",
      "about": "Deserunt amet qui ad aliqua ex reprehenderit. Tempor Lorem sit tempor et enim aliqua non aliquip. Deserunt voluptate nostrud consequat cillum cupidatat ea consequat Lorem sit cillum in laborum amet. Magna esse velit adipisicing exercitation excepteur eu qui do non adipisicing. Fugiat laboris proident dolor tempor incididunt dolore.\r\n",
      "registered": "2015-04-09T10:50:50 -02:00",
      "latitude": -76.371709,
      "longitude": 155.61306,
      "tags": [
        "dolore",
        "do",
        "commodo",
        "consequat",
        "ut",
        "proident",
        "sint"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Estella Newman"
        },
        {
          "id": 1,
          "name": "Perkins Noble"
        },
        {
          "id": 2,
          "name": "Desiree Cox"
        }
      ],
      "greeting": "Hello, Madelyn Gilliam! You have 8 unread messages.",
      "favoriteFruit": "banana"
    },
    {
      "_id": "658dacabf098df19dcabd5c1",
      "index": 15,
      "guid": "3185daf5-378b-460a-9125-dc238bedba10",
      "isActive": true,
      "balance": "$1,174.82",
      "picture": "http://placehold.it/32x32",
      "age": 39,
      "eyeColor": "green",
      "name": "Margret Gould",
      "gender": "female",
      "company": "PLUTORQUE",
      "email": "margretgould@plutorque.com",
      "phone": "+1 (931) 451-3529",
      "address": "590 Hubbard Street, Cavalero, Iowa, 2122",
      "about": "Sit labore et exercitation reprehenderit esse. Ea officia ut cillum cupidatat cupidatat qui esse enim esse. Sint mollit velit laborum eu mollit cillum aute eu ea minim. Excepteur non excepteur adipisicing esse officia in cupidatat excepteur non ea aliquip magna consectetur ullamco.\r\n",
      "registered": "2015-03-22T10:22:46 -01:00",
      "latitude": 5.912701,
      "longitude": 88.080747,
      "tags": [
        "sit",
        "deserunt",
        "commodo",
        "esse",
        "aliquip",
        "labore",
        "deserunt"
      ],
      "friends": [
        {
          "id": 0,
          "name": "Wilcox Singleton"
        },
        {
          "id": 1,
          "name": "Tisha Patton"
        },
        {
          "id": 2,
          "name": "Ericka Castaneda"
        }
      ],
      "greeting": "Hello, Margret Gould! You have 7 unread messages.",
      "favoriteFruit": "apple"
    }
  ]
)";

} // namespace liminal_json_io_test


#endif // LIMINAL_TESTS_LIMINAL_JSON_IO_HPP_